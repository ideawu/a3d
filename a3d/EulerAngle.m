//  Created by ideawu on 07/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "EulerAngle.h"

static void quat_to_euler(GLKQuaternion q, float *roll, float *pitch, float *yaw, const char *mode);


@interface EulerAngle(){
	char _mode[4];
}
@end


@implementation EulerAngle

+ (EulerAngle *)angleOfMatrix:(GMatrix4 *)matrix{
	EulerAngle *ret = [[EulerAngle alloc] initWithMatrix:matrix];
	return ret;
}

- (id)initWithMatrix:(GMatrix4 *)matrix{
	self = [super init];
	strcpy(_mode, "YZX");
	strcpy(_mode, "ZXY");
	[self parseMatrix:matrix];
	return self;
}

- (NSString *)description{
	return [NSString stringWithFormat:@"roll(%c): %.2f, pitch(%c): %.2f, yaw(%c): %.2f",
			_mode[0], _roll, _mode[1], _pitch, _mode[2], _yaw];
}

- (void)reset{
	_roll = _pitch = _yaw = 0;
}

- (void)parseMatrix:(GMatrix4 *)matrix{
	GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(matrix.matrix);
	quat_to_euler(quat, &_roll, &_pitch, &_yaw, _mode);
	_roll = GLKMathRadiansToDegrees(_roll);
	_pitch = GLKMathRadiansToDegrees(_pitch);
	_yaw = GLKMathRadiansToDegrees(_yaw);
}

@end


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
