//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Bitmap.h"
#include <CoreServices/CoreServices.h>

namespace a3d{

	Bitmap* Bitmap::create(int width, int height){
		char *pixels = (char *)malloc(4 * width * height);
		return Bitmap::createWithPixels(pixels, width, height);
	}

	Bitmap* Bitmap::createWithPixels(char *pixels, int width, int height){
		Bitmap *ret = new Bitmap();
		ret->_pixels = pixels;
		ret->_width = width;
		ret->_height = height;
		return ret;
	}

	Bitmap* Bitmap::createFromCGImage(const CGImageRef image){
		int w = (int)CGImageGetWidth(image);
		int h = (int)CGImageGetHeight(image);
		Bitmap *ret = Bitmap::create(w, h);
		CGContextRef context = ret->CGContext();
		if(!context){
			delete ret;
			return NULL;
		}
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
			return NULL;
		}
		Bitmap *ret = Bitmap::createFromCGImage(image);
		CGImageRelease(image);
		return ret;
	}

	Bitmap::Bitmap(){
		_pixels = NULL;
		_CGImage = NULL;
		_CGContext = NULL;
	}

	Bitmap::~Bitmap(){
		free(_pixels);
		CGImageRelease(_CGImage);
		CGContextRelease(_CGContext);
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
	
	CGContextRef Bitmap::CGContext(){
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

	CGImageRef Bitmap::CGImage(){
		if(!_CGImage){
			CGContextRef context = this->CGContext();
			if(context){
				_CGImage = CGBitmapContextCreateImage(context);
			}
		}
		return _CGImage;
	}

	bool Bitmap::savePNGFile(const char *filename){
		bool ret = false;
		CFURLRef url = NULL;
		CGImageDestinationRef dest = NULL;
		CGImageRef imageRef = NULL;
		if(!imageRef){
			goto end;
		}
		url = CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8 *)filename, strlen(filename), false);
		if(!url){
			goto end;
		}
		dest = CGImageDestinationCreateWithURL(url, kUTTypePNG, 1, NULL);
		if(!dest){
			goto end;
		}
		imageRef = this->CGImage();
		CGImageDestinationAddImage(dest, imageRef, nil);
		if(!CGImageDestinationFinalize(dest)){
			goto end;
		}
		ret = true;
	end:
		if(url){CFRelease(url);}
		if(dest){CFRelease(dest);}
		CGImageRelease(imageRef);
		return ret;
	}

}; // end namespace
