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
@end


@implementation GFollow

- (id)init{
	self = [super init];
	_mode = FollowTranslate | FollowRotateX | FollowRotateY | FollowRotateZ;
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

// 消除超过某些精度的小数部分，避免如 -0.00001 这样的数影响符号位。
static float trimf(float f){
	return fabs(f)<FLT_EPSILON*10? 0 : f;
}

static void quat_to_euler(GLKQuaternion q, float *roll, float *pitch, float *yaw, const char *mode){
	float r, p, y, w;
	float sinr, cosr, sinp, siny, cosy;
	float qs[3] = {q.x, q.y, q.z};
	// 各轴顺序
	int idx[3] = {mode[0]-'X', mode[1]-'X', mode[2]-'X'};
	r = qs[idx[0]];
	p = qs[idx[1]];
	y = qs[idx[2]];
	w = q.w;
	sinr = 2 * (w * r + p * y);
	cosr = 1 - 2 * (r * r + p * p);
	sinp = 2 * (w * p - r * y);
	siny = 2 * (w * y + r * p);
	cosy = 1 - 2 * (p * p + y * y);
	sinr = trimf(sinr);
	cosr = trimf(cosr);
	sinp = trimf(sinp);
	siny = trimf(siny);
	cosy = trimf(cosy);
	
	r = atan2(sinr, cosr);
	if (fabs(sinp) >= 1){
		p = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	}else{
		p = asin(sinp);
	}
	y = atan2(siny, cosy);
	
//	log_debug(@"%f %f %f", r, p, y);
//	log_debug(@"%f %f (%f) %f %f", sinr, cosr, sinp, siny, cosy);

	*roll = r;
	*pitch = p;
	*yaw = y;
}

- (GLKMatrix4)matrix{
	GLKMatrix4 old = _startMatrix;
	GLKMatrix4 now = _target.matrix;
	// T*A=B => T=B*A'
	GLKMatrix4 diff = GLKMatrix4Multiply(now, GLKMatrix4Invert(old, NULL));
//	return diff;
//	GLKQuaternion quat1 = GLKQuaternionMakeWithMatrix4(old);
//	GLKQuaternion quat2 = GLKQuaternionMakeWithMatrix4(now);
//	log_debug(@"quat: %f %f %f %f", quat.x, quat.y, quat.z, quat.w);
//	log_debug(@"quat: %f %f %f %f", quat.x, quat.y, quat.z, quat.w);

	GLKMatrix4 mat = GLKMatrix4MakeTranslation(0, 0, 0);
	if(_mode & FollowTranslate){
		GLKVector4 vec0 = GLKMatrix4MultiplyVector4(old, GLKVector4Make(0, 0, 0, 1));
		GLKVector4 vec1 = GLKMatrix4MultiplyVector4(now, GLKVector4Make(0, 0, 0, 1));
		vec1 = GLKVector4Subtract(vec1, vec0);
//		log_debug(@"vec1: %f %f %f %f", vec1.x, vec1.y, vec1.z, vec1.w);
		mat = GLKMatrix4Translate(mat, vec1.x, vec1.y, vec1.z);
	}
	
#if 1
	float roll, pitch, yaw;
	GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(diff);
	quat_to_euler(quat, &roll, &pitch, &yaw, "YXZ");
	log_debug(@"y: %f x: %f z: %f", GLKMathRadiansToDegrees(roll), GLKMathRadiansToDegrees(pitch), GLKMathRadiansToDegrees(yaw));
	if(_mode & FollowRotateY){
		mat = GLKMatrix4RotateY(mat, roll);
	}
	if(_mode & FollowRotateX){
		mat = GLKMatrix4RotateX(mat, pitch);
	}
	if(_mode & FollowRotateZ){
		mat = GLKMatrix4RotateZ(mat, yaw);
	}
//	log_debug(@"mat \n%@", [NSStringFromGLKMatrix4(mat) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
#else
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
	GLKMatrix4 mat2 = GLKMatrix4MakeWithQuaternion(quat);
	mat = GLKMatrix4Multiply(mat, mat2);
//	log_debug(@"diff \n%@", [NSStringFromGLKMatrix4(diff) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
//	log_debug(@"\n%@", [NSStringFromGLKMatrix4(mat) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
#endif
	return mat;
	return GLKMatrix4Invert(mat, NULL);
}

@end
