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

	Bitmap* Bitmap::createWithCGImage(CGImageRef imageRef){
		size_t w = CGImageGetWidth(imageRef);
		size_t h = CGImageGetHeight(imageRef);
		char *pixels = (char *)malloc(4 * w * h);
		
		CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
		uint32_t bitmapInfo = kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big;
		CGContextRef context = CGBitmapContextCreate(pixels, w, h, 8, 4 * w, colorSpace, bitmapInfo);
		CGColorSpaceRelease(colorSpace);
		// flip
		//		CGContextTranslateCTM(context, 0.0, h);
		//		CGContextScaleCTM(context, 1.0, -1.0);
		// Set the blend mode to copy before drawing since the previous contents of memory aren't used.
		// This avoids unnecessary blending.
		CGContextSetBlendMode(context, kCGBlendModeCopy);
		CGContextDrawImage(context, CGRectMake(0, 0, w, h), imageRef);
		CGContextRelease(context);
		
		return Bitmap::createWithPixels(pixels, (int)w, (int)h);
	}

	Bitmap::Bitmap(){
		_pixels = NULL;
	}

	Bitmap::~Bitmap(){
		free(_pixels);
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
	
	CGImageRef Bitmap::createCGImage(){
		size_t w = _width;
		size_t h = _height;
		
		CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
		uint32_t bitmapInfo = kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big;
		CGContextRef context = CGBitmapContextCreate(_pixels, w, h, 8, 4 * w, colorSpace, bitmapInfo);
		CGColorSpaceRelease(colorSpace);
		CGImageRef imageRef = CGBitmapContextCreateImage(context);
		return imageRef;
	}

	bool Bitmap::savePNGFile(const char *filename){
		bool ret = false;
		CFURLRef url = NULL;
		CGImageDestinationRef dest = NULL;
		CGImageRef imageRef = NULL;
		
		url = CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8 *)filename, strlen(filename), false);
		if(!url){
			goto ret;
		}
		dest = CGImageDestinationCreateWithURL(url, kUTTypePNG, 1, NULL);
		if(!dest){
			goto ret;
		}
		imageRef = createCGImage();
		CGImageDestinationAddImage(dest, imageRef, nil);
		if(!CGImageDestinationFinalize(dest)){
			goto ret;
		}
		ret = true;
	ret:
		CFRelease(url);
		CFRelease(dest);
		CGImageRelease(imageRef);
		return ret;
	}

}; // end namespace
