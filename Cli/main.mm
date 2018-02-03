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
