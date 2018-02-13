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
	Quaternion q;

	for(int i=1; i<20; i++){
		Matrix4 mat;
		mat.quaternion(Quaternion(i, vec));
//		log_debug(@"%@", NSStringFromGLKQuaternion(mat.quaternion()._quat));
//		log_debug(@"%f %s", mat.quaternion().angle(), mat.quaternion().vector().str().c_str());
//		log_debug(@"\n%s", mat.str().c_str());
		mat.scale(2);
//		log_debug(@"\n%s", mat.str().c_str());
		q = mat.quaternion();
		log_debug(@"%@", NSStringFromGLKQuaternion(q._quat));
		log_debug(@"in: %d out: %f, %s", i, q.angle(), q.vector().str().c_str());
		log_debug(@"");
	}

	log_debug(@"");

//	{
//		GLKQuaternion q = GLKQuaternionMakeWithAngleAndAxis(GLKMathDegreesToRadians(120), 0, 0, 1);
//		GLKMatrix4 mat = GLKMatrix4MakeWithQuaternion(q);
//		q = GLKQuaternionMakeWithMatrix4(mat);
//		log_debug(@"%@", NSStringFromGLKQuaternion(q));
//		log_debug(@"%f %@", GLKMathRadiansToDegrees(GLKQuaternionAngle(q)), NSStringFromGLKVector3(GLKQuaternionAxis(q)));
//		mat = GLKMatrix4Scale(mat, 1.41, 1.41, 1.41);
//		q = GLKQuaternionMakeWithMatrix4(mat);
////		log_debug(@"%f", 2 * GLKMathRadiansToDegrees(acos(q.w)));
////		log_debug(@"%@", NSStringFromGLKQuaternion(q));
////		q = GLKQuaternionNormalize(q);
////		log_debug(@"%f", 2 * GLKMathRadiansToDegrees(acos(q.w)));
//		log_debug(@"%@", NSStringFromGLKQuaternion(q));
//		log_debug(@"%f %@", GLKMathRadiansToDegrees(GLKQuaternionAngle(q)), NSStringFromGLKVector3(GLKQuaternionAxis(q)));
//	}

	return 0;
}

