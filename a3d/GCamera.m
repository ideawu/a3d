//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"
#import "GFollow.h"

@interface GCamera(){
	GObject *_target;
	GFollow *_follow;
}
// 观察的焦点在相机坐标系内的位置，默认为相机原点
@property GLKVector4 center;
@end

// 相机跟随算法：开始跟随时，记录相机原点和目标原点的坐标。

@implementation GCamera

- (id)init{
	self = [super init];
	_center = GLKVector4Make(110, 110, 110, 1); // TODO
	return self;
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
	
		log_debug(@"%f %f %f", r, p, y);
		log_debug(@"%f %f (%f) %f %f", sinr, cosr, sinp, siny, cosy);
	
	*roll = r;
	*pitch = p;
	*yaw = y;
}

- (GLKMatrix4)matrix{
//	GLKMatrix4 mat = super.matrix;
//	if(_follow){
//		mat = GLKMatrix4Multiply(GLKMatrix4Invert(_follow.startMatrix, NULL), mat);
//		mat = GLKMatrix4Multiply(_follow.target.matrix, mat);
//	}
//	return mat;

	GLKMatrix4 mat = super.matrix;
	if(_follow){
		float roll, pitch, yaw;
		GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(_follow.matrix);
		quat_to_euler(quat, &roll, &pitch, &yaw, "YXZ");
		log_debug(@"y: %f x: %f z: %f", GLKMathRadiansToDegrees(roll), GLKMathRadiansToDegrees(pitch), GLKMathRadiansToDegrees(yaw));
		GLKMatrix4 old = super.matrix;
		[self rotateY:GLKMathRadiansToDegrees(roll)];
		[self rotateX:GLKMathRadiansToDegrees(pitch)];
		[self rotateZ:GLKMathRadiansToDegrees(yaw)];
//		[self rotateX:GLKMathRadiansToDegrees(pitch) y:GLKMathRadiansToDegrees(roll) z:GLKMathRadiansToDegrees(yaw)];
//		mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
//		mat = GLKMatrix4Multiply(mat, _follow.matrix);
//		mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
		mat = super.matrix;
		super.matrix = old;
	}
	return mat;
}

#pragma mark - 目标跟随

- (GObject *)target{
//	return _target;
	return _follow.target;
}

// 跟随有几种模式：位移，X，Y，Z各轴旋转的跟随应该单独可配。
- (void)follow:(GObject *)target{
	if(_follow){
		[self unfollow];
	}
	GLKVector4 pos = GLKVector4Make(target.x, target.y, target.z, 1);
	log_debug(@"target: %f %f %f", target.x, target.y, target.z);
	log_debug(@"self: %f %f %f", self.x, self.y, self.z);
	_center = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(self.matrix, NULL), pos);
	log_debug(@"center: %f %f %f", _center.x, _center.y, _center.z);
	_follow = [[GFollow alloc] init];
	_follow.target = target;
}

- (void)unfollow{
	if(_follow){
		super.matrix = self.matrix;
		_center = GLKVector4Make(0, 0, 0, 1);
	}
	_follow = nil;
}

// 相机的移动以视线坐标为基准来移动
- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKMatrix4 mat = self.matrix;
	mat = GLKMatrix4Translate(mat, x, y, z);
	super.matrix = mat;
}

// 相机平移到焦点处后绕自身X轴旋转
- (void)rotateX:(float)degree{
	GLKMatrix4 mat = super.matrix;
	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
	mat = GLKMatrix4RotateX(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
	super.matrix = mat;
}

// 相机平移到焦点处后，绕经过自身原点的世界坐标Y轴的平行轴
- (void)rotateY:(float)degree{
//	GLKMatrix4 mat = super.matrix;
//	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
//	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
//	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
//	super.matrix = mat;

//	GLKMatrix4 mat = super.matrix;
//	GLKVector4 axis = GLKVector4Make(0, 1, 0, 1); // 世界Y轴
//	axis = GLKMatrix4MultiplyVector3(GLKMatrix4Invert(mat, NULL), axis); // 世界Y轴进入相机坐标系(移到相机原点)
//	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
//	mat = GLKMatrix4RotateWithVector3(mat, GLKMathDegreesToRadians(degree), axis);
//	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
//	super.matrix = mat;
	
	// P * -P * N * T * -N * P

	GLKMatrix4 mat = GLKMatrix4MakeTranslation(_center.x, _center.y, _center.z);
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
	mat = GLKMatrix4Multiply(mat, super.matrix);
	super.matrix = mat;
}

// 相机平移到焦点处后绕自身Z轴旋转
- (void)rotateZ:(float)degree{
	GLKMatrix4 mat = super.matrix;
	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
	mat = GLKMatrix4RotateZ(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
	super.matrix = mat;
}

// 按相机特有的操作顺序，先后旋转 z-y-z 轴
- (void)rotateX:(float)x y:(float)y z:(float)z{
	[self rotateZ:z];
	[self rotateY:y];
	[self rotateX:x];
}

@end
