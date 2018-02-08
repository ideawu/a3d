//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "ImageSprite.h"
#include "Renderer.h"
#include "Bitmap.h"

static CGImageSourceRef load_CGImageSource(const char *filename);
static double get_duration(CGImageSourceRef src, int index);

namespace a3d{
	ImageSprite* ImageSprite::createFromBitmap(const Bitmap &bitmap){
		Texture *texture = Texture::createFromBitmap(bitmap);
		if(!texture){
			return NULL;
		}
		ImageSprite *ret = new ImageSprite();
		ret->_texture = texture;
		ret->_durations.push_back(0);
		ret->frames(1);
		ret->duration(0);
		ret->width(bitmap.width());
		ret->height(bitmap.height());
		return ret;
	}

	ImageSprite* ImageSprite::createFromFile(const char *filename){
		ImageSprite *ret = new ImageSprite();
		ret->loadFromFile(filename);
		if(ret->frames() == 0){
			delete ret;
			return NULL;
		}
		return ret;
	}

	ImageSprite::ImageSprite():Sprite(){
		_texture = NULL;
		_cgimgSrc = NULL;
	}

	ImageSprite::~ImageSprite(){
		if(_cgimgSrc){
			CFRelease(_cgimgSrc);
		}
		delete _texture;
	}
	
	void ImageSprite::loadFromFile(const char *filename){
		this->_cgimgSrc = load_CGImageSource(filename);
		if(!this->_cgimgSrc){
			return;
		}
		int frames = (int)CGImageSourceGetCount(this->_cgimgSrc);
		if(frames == 0){
			return;
		}
		
		double total_duration = 0;
		for(int i=0; i<frames; i++){
			double duration = get_duration(this->_cgimgSrc, i);
			this->_durations.push_back(duration);
			total_duration += duration;
//			log_debug("frame: %d, duration: %.3f", i, duration);
		}

		this->frames(frames);
		this->duration(total_duration);
		// 加载第1张图片，生成width,height
		this->textureAtFrame(0, NULL);
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
		
		Bitmap *bitmap = Bitmap::createFromCGImageSourceAtIndex(_cgimgSrc, frame);
		if(!bitmap){
			return NULL;
		}
		if(!_texture){
			_texture = new Texture();
			this->width(bitmap->width());
			this->height(bitmap->height());
		}
		_texture->loadBitmap(*bitmap);
		delete bitmap;
		if(duration){
			*duration = _durations[frame];
		}
		return _texture;
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

static double get_duration(CGImageSourceRef src, int index){
	double duration = 0;
	CFDictionaryRef properties = CGImageSourceCopyPropertiesAtIndex(src, index, NULL);
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
	return duration;
}

