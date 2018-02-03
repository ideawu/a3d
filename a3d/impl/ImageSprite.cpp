//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "ImageSprite.h"
#include "Renderer.h"
#include "Bitmap.h"

static CGImageSourceRef load_CGImageSource(const char *filename);

namespace a3d{

	ImageSprite::ImageSprite(){
		_cgimgSrc = NULL;
	}

	ImageSprite::~ImageSprite(){
		if(_cgimgSrc){
			CFRelease(_cgimgSrc);
		}
		for(int i=0; i<_textures.size(); i++){
			delete _textures[i];
		}
	}

	ImageSprite* ImageSprite::create(const char *filename){
		CGImageSourceRef src = load_CGImageSource(filename);
		if(!src){
			return NULL;
		}
		
		std::vector<double> durations;
		double total_duration = 0;
		int frames = (int)CGImageSourceGetCount(src);
		
		for(int i=0; i<frames; i++){
			double duration = 0;
			CFDictionaryRef properties = CGImageSourceCopyPropertiesAtIndex(src, i, NULL);
			if (properties) {
				CFDictionaryRef gifProperties = (CFDictionaryRef)CFDictionaryGetValue(properties, kCGImagePropertyGIFDictionary);
				if (gifProperties) {
					CFTypeRef val;
					val = CFDictionaryGetValue(gifProperties, kCGImagePropertyGIFUnclampedDelayTime);
					if (val) {
						CFNumberGetValue((CFNumberRef)val, kCFNumberDoubleType, (void *)&duration);
					}
					if(duration == 0){
						val = CFDictionaryGetValue(gifProperties, kCGImagePropertyGIFDelayTime);
						if(val){
							CFNumberGetValue((CFNumberRef)val, kCFNumberDoubleType, (void *)&duration);
						}
					}
				}
				CFRelease(properties);
			}
			durations.push_back(duration);
			total_duration += duration;
//			log_debug("frame: %d, duration: %.3f", i, duration);
		}

		ImageSprite *ret = new ImageSprite();
		ret->_cgimgSrc = src;
		ret->_durations = durations;
		ret->_frames = frames;
		ret->_duration = total_duration;
		ret->_textures.resize(frames, NULL);
		// 加载第1张图片，生成width,height
		ret->textureAtFrame(0, NULL);
		return ret;
	}

	int ImageSprite::frameAtTime(double time, double *duration){
		// 静态图片
		if(_duration == 0){
			return 0;
		}
		for(int i=0; i<_durations.size(); i++){
			time -= _durations[i];
			if(time < 0){
				if(duration){
					*duration = _durations[i];
				}
				return i;
			}
		}
		return -1;
	}

	Texture* ImageSprite::textureAtTime(double time, double *duration){
		int frame = frameAtTime(time, duration);
		return textureAtFrame(frame, NULL);
	}

	Texture* ImageSprite::textureAtFrame(int frame, double *duration){
		if(frame < 0 || frame >= _frames){
			return NULL;
		}
		if(_textures[frame] == NULL){
			Texture *texture = new Texture();
			_textures[frame] = texture;
			
			Bitmap *bitmap = Bitmap::createFromCGImageSourceAtIndex(_cgimgSrc, frame);
			if(!bitmap){
				return NULL;
			}
			this->width(bitmap->width());
			this->height(bitmap->height());
			texture->loadBitmap(*bitmap);
			delete bitmap;
		}
		if(duration){
			*duration = _durations[frame];
		}
		return _textures[frame];
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

