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
	GLKQuaternion q = GLKQuaternionMakeWithAngleAndAxis(GLKMathDegreesToRadians(45), 0, 0, 1);
	q = GLKQuaternionInvert(q);
	GLKVector3 axis = GLKQuaternionAxis(q);
	float angle = GLKQuaternionAngle(q);
	log_debug(@"%f %f %f %f", q.x, q.y, q.z, q.w);
	log_debug(@"%f %f %f", axis.x, axis.y, axis.z);
	log_debug(@"%f", GLKMathRadiansToDegrees(angle));
	return 0;
}
