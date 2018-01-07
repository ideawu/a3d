//  Created by ideawu on 07/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "EulerAngle.h"

// 欧拉角的旋转顺序是：旋转-上下-旋转，按此顺序指定各轴
static const int EulerAngleModeYX = 1;    // 如照相机，炮塔
static const int EulerAngleModeZX = 1<<1; // 如飞机

@interface EulerAngle(){
	char _mode[4];
}

@property float xMin;
@property float xMax;
@property float yMin;
@property float yMax;
@property float zMin;
@property float zMax;
@end


@implementation EulerAngle

- (id)init{
	self = [super init];
	strcpy(_mode, "YXZ");
	_xMin = -90;
	_xMax = 90;
	_yMin = FLT_MIN;
	_yMax = FLT_MAX;
	_zMin = 0;
	_zMax = 0;
	return self;
}

- (void)reset{
	_x = _y = _z = 0;
}

// 返回angle映射到[min, max]范围内的角度数
- (float)calculateAngle:(float)angle min:(float)min max:(float)max{
	float used = max - min;
	float spare = 360 - (used);
	angle = angle - (int)(angle/360.0) * 360;
	if(angle < min && angle > max){
		float ratio = 1 - (angle - max)/spare;
		angle = min + used * ratio;
	}
	return angle;
}

// 消除超过某些精度的小数部分，避免如 -0.00001 这样的数影响符号位。
static float trimf(float f){
	return fabs(f)<FLT_EPSILON*10? 0 : f;
}

- (void)setWithQuaternion:(GLKQuaternion)q{
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
	
	*roll = r;
	*pitch = p;
	*yaw = y;
}

//static void toEulerAngle(GLKQuaternion q, double *roll, double *pitch, double *yaw){
//	// roll/Forward/x
//	double sinr = 2.0 * (q.w * q.x + q.y * q.z);
//	double cosr = 1.0 - 2.0 * (q.x * q.x + q.y * q.y);
//	*pitch = atan2(sinr, cosr);
//	if(sinr == 0){
//		*pitch = 0;
//	}
//
//	// pitch/Right/y
//	double sinp = +2.0 * (q.w * q.y - q.z * q.x);
//	if (fabs(sinp) >= 1){
//		*yaw = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
//	}else{
//		*yaw = asin(sinp);
//	}
//
//	// yaw/Up/z
//	double siny = +2.0 * (q.w * q.z + q.x * q.y);
//	double cosy = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
//	log_debug(@"%f %f", siny, cosy);
//	*roll = atan2(siny, cosy);
//}


@end
