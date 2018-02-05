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
#include "IKit/IKit.h"

using namespace a3d;

int main(int argc, const char * argv[])
{
	NSView *view = [[NSView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
	view.wantsLayer = YES;
	view.layer = [[CALayer alloc] init];
	view.layer.frame = CGRectMake(0,0,200,200);
	view.layer.backgroundColor = [NSColor blueColor].CGColor;
	
	ILabel *iv = (ILabel *)[IView viewFromXml:@"<a style=\"color: #fff; font-size: 50\">123</a>"];
	[view addSubview:iv];
	[iv layout];
	iv.label.layer = [[CALayer alloc] init];
	iv.label.layer.frame = iv.bounds;
//	iv.label.layer.backgroundColor = [NSColor yellowColor].CGColor;

	NSImage *image = [[NSImage alloc] initWithSize:view.bounds.size];
	[image lockFocus];
	CGContextRef ctx = (CGContextRef)[NSGraphicsContext currentContext].graphicsPort;
//	[view layout];
//	[view display];
//	[view.layer renderInContext:ctx];
	[iv.layer renderInContext:ctx];
	[image unlockFocus];
	
	log_debug(@"%@ %f", iv, iv.frame.size.width);
	[[iv dataWithPDFInsideRect:iv.bounds] writeToFile:@"a.pdf" atomically:YES];

	[[image TIFFRepresentation] writeToFile:@"a.png" atomically:YES];

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
