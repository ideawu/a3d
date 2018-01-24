//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "ImageSprite.h"

static CGImageSourceRef load_CGImageSource(const char *filename);
static char* load_data_from_CGImage(CGImageRef image, int *width, int *height);

namespace a3d{

	ImageSprite::ImageSprite(){
		_cgimgSrc = NULL;
	}

	ImageSprite::~ImageSprite(){
		if(_cgimgSrc){
			CFRelease(_cgimgSrc);
		}
		for(int i=0; i<_texIdAtFrame.size(); i++){
			GLuint tid = _texIdAtFrame[i];
			if(tid > 0){
				glDeleteTextures(1, &tid);
			}
		}
	}

	ImageSprite* ImageSprite::create(const char *filename){
		CGImageSourceRef src = load_CGImageSource(filename);
		if(!src){
			return NULL;
		}
		
		std::vector<float> durations;
		float total_duration = 0;
		int frames = (int)CGImageSourceGetCount(src);
		
		for(int i=0; i<frames; i++){
			float duration = 0;
			CFDictionaryRef properties = CGImageSourceCopyPropertiesAtIndex(src, i, NULL);
			if (properties) {
				CFDictionaryRef gifProperties = (CFDictionaryRef)CFDictionaryGetValue(properties, kCGImagePropertyGIFDictionary);
				if (gifProperties) {
					CFTypeRef val;
					val = CFDictionaryGetValue(gifProperties, kCGImagePropertyGIFUnclampedDelayTime);
					if (val) {
						CFNumberGetValue((CFNumberRef)val, kCFNumberFloatType, (void *)&duration);
					}
					if(duration == 0){
						val = CFDictionaryGetValue(gifProperties, kCGImagePropertyGIFDelayTime);
						if(val){
							CFNumberGetValue((CFNumberRef)val, kCFNumberFloatType, (void *)&duration);
						}
					}
				}
				CFRelease(properties);
			}
			durations.push_back(duration);
			total_duration += duration;
	//		log_debug(@"frame: %d, duration: %.3f", i, duration);
		}

		ImageSprite *ret = new ImageSprite();
		ret->_cgimgSrc = src;
		ret->_durations = durations;
		ret->_frames = frames;
		ret->_duration = total_duration;
		ret->_texIdAtFrame.resize(frames, -1);
		// 加载第1张图片，生成width,height
		ret->textureAtFrame(0, NULL);
		return ret;
	}

	GLuint ImageSprite::bindImageData(const char *data, int width, int height){
		GLuint tid;
		glGenTextures(1, &tid);
		glBindTexture(GL_TEXTURE_2D, tid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // LINEAR 使用平均算法，抗锯齿
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
		return tid;
	}

	GLuint ImageSprite::textureAtFrame(int frame, float *duration){
		if(frame >= _frames){
			return 0;
		}
		if(_texIdAtFrame[frame] == -1){
			CGImageRef image = CGImageSourceCreateImageAtIndex(_cgimgSrc, frame, NULL);
			if(!image){
				_texIdAtFrame[frame] = 0;
				return 0;
			}
			int w, h;
			char *data = load_data_from_CGImage(image, &w, &h);
			CGImageRelease(image);
			
			if(!data){
				_texIdAtFrame[frame] = 0;
				return 0;
			}
			GLuint tid = bindImageData(data, w, h);
			_texIdAtFrame[frame] = tid;
//			log_debug("bind image to texture: %d, w: %d, h: %d", tid, w, h);
			
			free(data);
			
			this->width(w);
			this->height(h);
		}
		if(duration){
			*duration = _durations[frame];
		}
		return _texIdAtFrame[frame];
	}

	GLuint ImageSprite::textureAtTime(float time, float *duration){
		for(int i=0; i<_durations.size(); i++){
			time -= _durations[i];
			if(time < 0){
				return textureAtFrame(i, duration);
			}
		}
		return 0;
	}
	
}; // end namespace

static CGImageSourceRef load_CGImageSource(const char *filename){
	CFURLRef url = CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8 *)filename, strlen(filename), false);
	if(!url){
		return NULL;
	}
	CGImageSourceRef src = CGImageSourceCreateWithURL((CFURLRef)url, NULL);
	CFRelease(url);
	return src;
}

static char* load_data_from_CGImage(CGImageRef image, int *width, int *height){
	char *data = NULL;
	CGContextRef context = NULL;

	size_t w = CGImageGetWidth(image);
	size_t h = CGImageGetHeight(image);
	data = (char *)malloc(4 * w * h);
	
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	uint32_t bitmapInfo = kCGImageAlphaPremultipliedLast | kCGImageByteOrder32Big;
	context = CGBitmapContextCreate(data, w, h, 8, 4 * w, colorSpace, bitmapInfo);
	CGColorSpaceRelease(colorSpace);
	
	// flip
	//		CGContextTranslateCTM(context, 0.0, h);
	//		CGContextScaleCTM(context, 1.0, -1.0);
	// Set the blend mode to copy before drawing since the previous contents of memory aren't used.
	// This avoids unnecessary blending.
	CGContextSetBlendMode(context, kCGBlendModeCopy);
	CGContextDrawImage(context, CGRectMake(0, 0, w, h), image);
	
	CGContextRelease(context);
	if(width){
		*width = (int)w;
	}
	if(height){
		*height = (int)h;
	}
	return data;
}
