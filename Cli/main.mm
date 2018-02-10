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
	GLKQuaternion quat = GLKQuaternionMakeWithAngleAndAxis(1.0, 0, 0, 1);
	GLKVector3 v = GLKQuaternionAxis(quat);
	log_debug(@"%f %f %f", v.x, v.y, v.z);
	log_debug(@"%f %f %f %f", quat.x, quat.y, quat.z, quat.w);

	GLKMatrix4 mat = GLKMatrix4Identity;
	mat = GLKMatrix4Translate(mat, 800, 0, 800);
	Vector3 vec = Vector3(0, 0, 1);
	mat = GLKMatrix4Rotate(mat, degree_to_radian(90), vec.x, vec.y, vec.z);
	log_debug(@"%@", NSStringFromGLKMatrix4(mat));
	mat = GLKMatrix4Rotate(mat, degree_to_radian(90), vec.x, vec.y, vec.z);
	log_debug(@"%@", NSStringFromGLKMatrix4(mat));
	return 0;
}

