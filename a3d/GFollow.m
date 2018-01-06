//  Created by ideawu on 06/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GFollow.h"

static const int FollowTranslate = 1;
static const int FollowRotateX   = 1<<1;
static const int FollowRotateY   = 1<<2;
static const int FollowRotateZ   = 1<<3;

@interface GFollow(){
	GObject *_target;
}
@property int mode;
@property GLKMatrix4 startMatrix;
@end


@implementation GFollow

- (id)init{
	self = [super init];
	_mode = FollowTranslate | FollowRotateX | FollowRotateY;
	return self;
}

- (GObject *)target{
	return _target;
}

- (void)setTarget:(GObject *)target{
	_target = target;
	_startMatrix = target.matrix;
}

- (void)followTranslate{
	_mode |= FollowTranslate;
}

- (void)followRotate{
	[self followRotateX];
	[self followRotateY];
	[self followRotateZ];
}

- (void)followRotateX{
	_mode |= FollowRotateX;
}

- (void)followRotateY{
	_mode |= FollowRotateY;
}

- (void)followRotateZ{
	_mode |= FollowRotateZ;
}

- (GLKMatrix4)matrix{
	GLKMatrix4 now = _target.matrix;
	GLKMatrix4 old = _startMatrix;
//	log_debug(@"old \n%@", [NSStringFromGLKMatrix4(old) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
//	log_debug(@"new \n%@", [NSStringFromGLKMatrix4(now) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
	GLKMatrix4 diff = GLKMatrix4Multiply(now, GLKMatrix4Invert(old, NULL));
	GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(diff);
//	log_debug(@"quat: %f %f %f %f", quat.x, quat.y, quat.z, quat.w);
	
	GLKMatrix4 mat = GLKMatrix4MakeTranslation(0, 0, 0);
	if(_mode & FollowTranslate){
		GLKVector4 vec0 = GLKMatrix4MultiplyVector4(old, GLKVector4Make(0, 0, 0, 1));
		GLKVector4 vec1 = GLKMatrix4MultiplyVector4(now, GLKVector4Make(0, 0, 0, 1));
		vec1 = GLKVector4Subtract(vec1, vec0);
//		log_debug(@"vec1: %f %f %f %f", vec1.x, vec1.y, vec1.z, vec1.w);
		mat = GLKMatrix4Translate(mat, vec1.x, vec1.y, vec1.z);
	}
	if(!(_mode & FollowRotateX)){
		quat.x = 0;
	}
	if(!(_mode & FollowRotateY)){
		quat.y = 0;
	}
	if(!(_mode & FollowRotateZ)){
		quat.z = 0;
	}
	quat = GLKQuaternionNormalize(quat);
	log_debug(@"quat: %f %f %f %f", quat.x, quat.y, quat.z, quat.w);
	GLKMatrix4 mat2 = GLKMatrix4MakeWithQuaternion(quat);
	mat = GLKMatrix4Multiply(mat, mat2);
//	log_debug(@"diff \n%@", [NSStringFromGLKMatrix4(diff) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
//	log_debug(@"\n%@", [NSStringFromGLKMatrix4(mat) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
	return mat;

	// 或许可以用四元数来实现？
//	if(_mode & FollowRotateX){
//		// Y轴的变动角度，也即X轴旋转角度
//		GLKVector3 vec0 = GLKVector3Make(0, 1, 0);
//		GLKVector3 vec1 = GLKMatrix4MultiplyVector3(diff, vec0);
//		float dp = GLKVector3DotProduct(vec0, vec1);
//		float rad = fabs(dp - 1)<0.0001? 0 : acos(dp);
//		log_debug(@"x rotate: %f %f %f", dp, rad, GLKMathRadiansToDegrees(rad));
//		mat = GLKMatrix4RotateX(mat, rad);
//	}
//	if(_mode & FollowRotateY){
//		// X轴的变动角度，也即Y轴旋转角度
//		GLKVector3 vec0 = GLKVector3Make(1, 0, 0);
//		GLKVector3 vec1 = GLKMatrix4MultiplyVector3(diff, vec0);
//		float dp = GLKVector3DotProduct(vec0, vec1);
//		float rad = fabs(dp - 1)<0.0001? 0 : acos(dp);
//		log_debug(@"y rotate: %f %f %f", dp, rad, GLKMathRadiansToDegrees(rad));
//		mat = GLKMatrix4RotateY(mat, rad);
//	}
	
//	GLKQuaternion quat1 = GLKQuaternionMakeWithMatrix4(old);
//	GLKQuaternion quat2 = GLKQuaternionMakeWithMatrix4(now);
//	GLKQuaternion quat = GLKQuaternionSubtract(quat2, quat1);
//	quat.w = 1;
//	GLKVector3 offset = GLKVector3Make(now.m30-old.m30, now.m31-old.m31, now.m32-old.m32);
//	log_debug(@"%f %f %f %f", quat.x, quat.y, quat.z, quat.w);
//	if(!(_mode & FollowRotateZ)){
//		quat.z = 0;
//	}
//	GLKMatrix4 mat1 = GLKMatrix4MakeTranslation(offset.x, offset.y, offset.z);
//	GLKMatrix4 mat2 = GLKMatrix4MakeWithQuaternion(quat);
//	NSLog(@"\n%@", [NSStringFromGLKMatrix4(mat2) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
//	GLKMatrix4 mat = GLKMatrix4Multiply(mat2, mat1);
//	return mat;
}

@end
