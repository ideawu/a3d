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
#include "a3d.h"

using namespace a3d;

int main(int argc, const char * argv[])
{
	Vector3 vec = Vector3(0, 0, 1);
	Matrix4 mat;

	// 10.10 有 bug！
	mat.quaternion(Quaternion(120, vec));
	log_debug(@"%f", mat.quaternion().angle());
	mat.scale(1.41);
	log_debug(@"%f", mat.quaternion().angle());
	return 0;
}

