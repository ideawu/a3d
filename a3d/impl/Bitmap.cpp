//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Bitmap.h"
#include <CoreServices/CoreServices.h>

namespace a3d{
	static CGImageSourceRef load_CGImageSource(const char *filename){
		CFURLRef url = CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8 *)filename, strlen(filename), false);
		if(!url){
			return NULL;
		}
		CGImageSourceRef src = CGImageSourceCreateWithURL((CFURLRef)url, NULL);
		CFRelease(url);
		return src;
	}

	Bitmap* Bitmap::create(int width, int height){
		char *pixels = (char *)malloc(4 * width * height);
		return Bitmap::createWithPixels(pixels, width, height);
	}

	Bitmap* Bitmap::createFromFile(const char *filename){
		CGImageSourceRef imgSource = load_CGImageSource(filename);
		if(!imgSource){
			return NULL;
		}
		Bitmap *ret = Bitmap::createFromCGImageSourceAtIndex(imgSource, 0);
		CFRelease(imgSource);
		return ret;
	}

	Bitmap* Bitmap::createFromCGImage(const CGImageRef image){
		int w = (int)CGImageGetWidth(image);
		int h = (int)CGImageGetHeight(image);
		return createFromCGImage(image, w, h);
	}
	
	Bitmap* Bitmap::createFromCGImage(const CGImageRef image, int w, int h){
		Bitmap *ret = Bitmap::create(w, h);
		CGContextRef context = ret->CGContext();
		if(!context){
			delete ret;
			return NULL;
		}
		// 如果不在这里flip，那么需要在 draw texture 时 flip
		// flip
		//		CGContextTranslateCTM(context, 0.0, h);
		//		CGContextScaleCTM(context, 1.0, -1.0);
		// Set the blend mode to copy before drawing since the previous contents of memory aren't used.
		// This avoids unnecessary blending.
		CGContextSetBlendMode(context, kCGBlendModeCopy);
		CGContextDrawImage(context, CGRectMake(0, 0, w, h), image);
		return ret;
	}

	Bitmap* Bitmap::createFromCGImageSourceAtIndex(const CGImageSourceRef imageSource, int index){
		CGImageRef image = CGImageSourceCreateImageAtIndex(imageSource, index, NULL);
		if(!image){
			log_error("CGImageSourceCreateImageAtIndex %d failed", index);
			return NULL;
		}
		Bitmap *ret = Bitmap::createFromCGImage(image);
		CGImageRelease(image);
		return ret;
	}

	Bitmap* Bitmap::createWithPixels(char *pixels, int width, int height){
		Bitmap *ret = new Bitmap();
		ret->_pixels = pixels;
		ret->_width = width;
		ret->_height = height;
		return ret;
	}

	Bitmap::Bitmap(){
		_pixels = NULL;
		_CGImage = NULL;
		_CGContext = NULL;
//		log_debug("create %d", this);
	}

	Bitmap::~Bitmap(){
		free(_pixels);
		CGImageRelease(_CGImage);
		CGContextRelease(_CGContext);
//		log_debug("delete %d", this);
	}

	int Bitmap::width() const{
		return _width;
	}
	
	int Bitmap::height() const{
		return _height;
	}
	
	char* Bitmap::pixels() const{
		return _pixels;
	}
	
	const CGContextRef Bitmap::CGContext(){
		if(!_CGContext){
			size_t w = _width;
			size_t h = _height;
			CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
			uint32_t bitmapInfo = kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Host;
			_CGContext = CGBitmapContextCreate(_pixels, w, h, 8, 4 * w, colorSpace, bitmapInfo);
			CGColorSpaceRelease(colorSpace);
		}
		return _CGContext;
	}

	const CGImageRef Bitmap::CGImage(){
		CGImageRelease(_CGImage);
		_CGImage = NULL;
		
		CGContextRef context = this->CGContext();
		if(context){
			_CGImage = CGBitmapContextCreateImage(context);
		}
		return _CGImage;
	}

	bool Bitmap::savePNGFile(const char *filename){
		bool ret = false;
		CFURLRef url = NULL;
		CGImageDestinationRef dest = NULL;
		CGImageRef imageRef = this->CGImage();
		if(!imageRef){
			log_error("no CGImageRef");
			goto end;
		}
		url = CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8 *)filename, strlen(filename), false);
		if(!url){
			log_error("failed to create CFURL for %s", filename);
			goto end;
		}
		dest = CGImageDestinationCreateWithURL(url, kUTTypePNG, 1, NULL);
		if(!dest){
			log_error("failed to create img dst for %s", filename);
			goto end;
		}
		imageRef = this->CGImage();
		CGImageDestinationAddImage(dest, imageRef, nil);
		if(!CGImageDestinationFinalize(dest)){
			log_error("failed to save img dst to %s", filename);
			goto end;
		}
		ret = true;
	end:
		if(url){CFRelease(url);}
		if(dest){CFRelease(dest);}
		return ret;
	}

}; // end namespace
