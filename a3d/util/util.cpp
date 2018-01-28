//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "util.h"

namespace a3d{
	CGImageRef load_cgimage(const char *filename){
		CFURLRef url = CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8 *)filename, strlen(filename), false);
		if(!url){
			return NULL;
		}
		CGImageSourceRef src = CGImageSourceCreateWithURL((CFURLRef)url, NULL);
		CFRelease(url);
		if(!src){
			return NULL;
		}
		CGImageRef image = CGImageSourceCreateImageAtIndex(src, 0, NULL);
		CFRelease(src);
		return image;
	}
	
	char *load_image_data(const char *filename, int *width, int *height){
		char *data = NULL;
		CGImageRef image = NULL;
		CGContextRef context = NULL;
		
		image = load_cgimage(filename);
		if(!image){
			return NULL;
		}
		
		size_t w = CGImageGetWidth(image);
		size_t h = CGImageGetHeight(image);
		data = (char *)malloc(4 * w * h);
		
		CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
		uint32_t bitmapInfo = kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big;
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
		CGImageRelease(image);
		if(width){
			*width = (int)w;
		}
		if(height){
			*height = (int)h;
		}
		return data;
	}
}; // end namespace
