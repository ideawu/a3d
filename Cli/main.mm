//  Created by ideawu on 02/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

//int main(int argc, const char * argv[]) {
//	GLKMatrix4 mat = GLKMatrix4Identity;
//	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(181+100));
//	GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(mat);
//	GLKVector3 axis = GLKQuaternionAxis(quat);
//	float angle = GLKQuaternionAngle(quat);
//	log_debug(@"%.2f %.2f %.2f %.2f", axis.x, axis.y, axis.z, GLKMathRadiansToDegrees(angle));
//	return 0;
//}

#import <Cocoa/Cocoa.h>
//#import <ImageIO/ImageIO.h>
//#import <CoreGraphics/CoreGraphics.h>
#include "TextSpirte.h"
#include "Bitmap.h"
#include "Text.h"

using namespace a3d;

static char* textToImage(const char *str, int maxWidth, int *outWidth, int *outHeight){
	int maxHeight = 10000;
	float fontSize = 40;
	CFStringRef fontFamily = CFSTR("Helvetica Light");
	CTFontRef font = CTFontCreateWithName(fontFamily, fontSize, nil);
	
	CFStringRef keys[] = {kCTFontAttributeName};
	CFTypeRef values[] = {font};
	CFDictionaryRef attributes = CFDictionaryCreate(
													kCFAllocatorDefault, (const void**)&keys,
													(const void**)&values, sizeof(keys) / sizeof(keys[0]),
													&kCFTypeDictionaryKeyCallBacks,
													&kCFTypeDictionaryValueCallBacks);
	
	CFStringRef string = CFStringCreateWithCStringNoCopy(NULL, str, kCFStringEncodingUTF8, kCFAllocatorNull);
//	CFStringRef string = CFStringCreateWithCString(NULL, text, kCFStringEncodingUTF8);
	CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);
	
	int w = 0;
	int h = 0;
	
	Text text(str);
	text.maxWidth(maxWidth);
	text.maxHeight(maxHeight);
	text.calculateSize(&w, &h);
	
//	sizeForAttributedString(attrString, maxWidth, maxHeight, &w, &h);
	if(w == 0 || h == 0){
		return NULL;
	}
	
	log_debug("%d %d", w, h);
	char *pixels = (char *)malloc(4 * w * h);
	
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	uint32_t bitmapInfo = kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big;
	CGContextRef context = CGBitmapContextCreate(pixels, w, h, 8, 4 * w, colorSpace, bitmapInfo);
	CGColorSpaceRelease(colorSpace);

	{
		CGMutablePathRef path = CGPathCreateMutable();
		CGRect bounds = CGRectMake(0, 0, w, h);
		CGPathAddRect(path, NULL, bounds);
		CTFramesetterRef framesetter = CTFramesetterCreateWithAttributedString(attrString);
		CTFrameRef frame = CTFramesetterCreateFrame(framesetter, CFRangeMake(0, 0), path, NULL);

		CTFrameDraw(frame, context);
		
		CFRelease(frame);
		CFRelease(path);
		CFRelease(framesetter);
	}
	
	CGContextRelease(context);

	CFRelease(string);
	CFRelease(attributes);

	if(outWidth){
		*outWidth = (int)w;
	}
	if(outHeight){
		*outHeight = (int)h;
	}

	return pixels;
}

int main(int argc, const char * argv[])
{
	Text text("你好!\nHello World!");
	Bitmap *bitmap = text.drawToBitmap();
	if(!bitmap){
		log_debug(@"error");
		return 0;
	}
	bitmap->savePNGFile("a.png");
	delete bitmap;


//	@autoreleasepool {
//		NSString *string = @"Hello, World!";
//		NSString *path = [[[NSProcessInfo processInfo] arguments] objectAtIndex:1];
//
//		NSDictionary *attributes =
//		@{ NSFontAttributeName : [NSFont fontWithName:@"Helvetica" size:40.0],
//		   NSForegroundColorAttributeName : NSColor.blackColor};
//
//		NSImage *image = [[NSImage alloc] initWithSize:[string sizeWithAttributes:attributes]];
//		[image lockFocus];
//		[string drawAtPoint:NSZeroPoint withAttributes:attributes];
//		[image unlockFocus];
//
//		NSData *imageData = [image TIFFRepresentation];
//		NSBitmapImageRep *imageRep = [NSBitmapImageRep imageRepWithData:imageData];
//
////		[[image TIFFRepresentation] writeToFile:path atomically:YES];
//	}
	return 0;
}
