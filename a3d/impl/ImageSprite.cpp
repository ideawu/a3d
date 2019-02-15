//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "ImageSprite.h"
#include "Renderer.h"
#include "Bitmap.h"

static CGImageSourceRef load_CGImageSource(const char *filename);
static double get_duration(CGImageSourceRef src, int index);

namespace a3d{

	ImageSprite* ImageSprite::create(){
		ImageSprite *ret = new ImageSprite();
		return ret;
	}

	ImageSprite* ImageSprite::createFromBitmap(const Bitmap &bitmap){
		Texture *texture = Texture::createFromBitmap(bitmap);
		if(!texture){
			return NULL;
		}
		return createWithTexture(texture);
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

	ImageSprite* ImageSprite::createWithTexture(Texture *texture){
		ImageSprite *ret = new ImageSprite();
		ret->addTexture(texture, 0);
		return ret;
	}

	ImageSprite::ImageSprite():Sprite(){
		_cgimgSrc = NULL;
	}

	ImageSprite::~ImageSprite(){
		if(_cgimgSrc){
			CFRelease(_cgimgSrc);
		}
		for(std::vector<Texture *>::iterator it=_textures.begin(); it!=_textures.end(); it++){
			Texture *texture = *it;
			delete texture;
		}
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
		this->_textures.resize(frames, NULL);
		// 加载第1张图片，生成width,height
		this->textureAtFrame(0, NULL);
	}

	int ImageSprite::frameAtTime(double time, double *duration){
		// 静态图片
		if(_duration == 0){
			return 0;
		}
		int idx = 0;
		if(time <= 0){
			idx = 0;
		}else if(time >= _duration){
			idx = _frames - 1;
		}else{
			for(int i=0; i<_durations.size(); i++){
				time -= _durations[i];
				if(time <= 0){
					idx = i;
					break;
				}
			}
		}
		if(duration){
			*duration = _durations[idx];
		}
		return idx;
	}

	Texture* ImageSprite::textureAtTime(double time, double *duration){
		int frame = frameAtTime(time, duration);
		return textureAtFrame(frame, NULL);
	}

	Texture* ImageSprite::textureAtFrame(int frame, double *duration){
		if(frame < 0 || frame >= _frames){
			return NULL;
		}
		if(!_textures[frame]){
			Bitmap *bitmap = Bitmap::createFromCGImageSourceAtIndex(_cgimgSrc, frame);
			if(!bitmap){
				log_debug("failed to create bitmap from CGImage");
				return NULL;
			}
			this->width(bitmap->width());
			this->height(bitmap->height());
			Texture *texture = Texture::createFromBitmap(*bitmap);
			_textures[frame] = texture;
			delete bitmap;
		}
		if(duration){
			*duration = _durations[frame];
		}
		return _textures[frame];
	}

	void ImageSprite::addTexture(Texture *texture, double duration){
		_frames += 1;
		_duration += duration;
		_durations.push_back(duration);
		_textures.push_back(texture);
		this->width(texture->width());
		this->height(texture->height());
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

