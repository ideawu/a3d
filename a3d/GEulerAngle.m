//  Created by ideawu on 07/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GEulerAngle.h"

static float angle(GLKVector3 vec0, GLKVector3 vec1, GLKVector3 direction);
static void quat_to_euler(GLKQuaternion q, float *roll, float *pitch, float *yaw, const char *mode);


@interface GEulerAngle(){
	char _mode[4];
}
@end


@implementation GEulerAngle

+ (GEulerAngle *)angleWithMatrix:(GMatrix4 *)matrix{
	return [GEulerAngle angleWithMatrix:matrix mode:NULL];
}

+ (GEulerAngle *)angleWithMatrix:(GMatrix4 *)matrix mode:(const char *)mode{
	GEulerAngle *ret = [[GEulerAngle alloc] initWithMatrix:matrix mode:mode];
	return ret;
}

- (id)init{
	self = [super init];
	[self reset];
	strcpy(_mode, "ZXY");
	return self;
}

- (id)initWithMatrix:(GMatrix4 *)matrix{
	return [self initWithMatrix:matrix mode:NULL];
}

- (id)initWithMatrix:(GMatrix4 *)matrix mode:(const char *)mode{
	self = [self init];
	if(mode){
		strncpy(_mode, mode, 3);
	}
	[self parseMatrix:matrix];
	return self;
}

- (NSString *)description{
	return [NSString stringWithFormat:@"roll(%c): %.2f, pitch(%c): %.2f, yaw(%c): %.2f",
			_mode[0], _roll, _mode[1], _pitch, _mode[2], _yaw];
}

- (GLKMatrix4)matrix{
	GLKMatrix4 mat = GLKMatrix4Identity;
	mat = [self rotateMatrix:mat degree:_roll axis:_mode[0]];
	mat = [self rotateMatrix:mat degree:_pitch axis:_mode[1]];
	mat = [self rotateMatrix:mat degree:_yaw axis:_mode[2]];
	return mat;
}

- (GLKMatrix4)rotateMatrix:(GLKMatrix4)mat degree:(float)degree axis:(char)c{
//	if(degree != 0){
//		log_debug(@"%c %f", c, degree);
//	}
	float radian = GLKMathDegreesToRadians(degree);
	if(c == 'X'){
		mat = GLKMatrix4RotateX(mat, radian);
	}else if(c == 'Y'){
		mat = GLKMatrix4RotateY(mat, radian);
	}else if(c == 'Z'){
		mat = GLKMatrix4RotateZ(mat, radian);
	}
	return mat;
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
	
//	log_debug(@"--- %@", self);

	
	// 当前坐标轴
	GLKVector3 ax = matrix.xAxis;
	GLKVector3 ay = matrix.yAxis;
	GLKVector3 az = matrix.zAxis;
	
	GLKVector3 ox = GLKVector3Make(1, 0, 0);
	GLKVector3 oy = GLKVector3Make(0, 1, 0);
//	GLKVector3 oz = GLKVector3Make(0, 0, 1);
	
	if(trimf(1 - fabs(az.y)) == 0){ // Z轴是否与Y轴重合
		_roll = 0;
	}else{
		GLKVector3 prj = GLKVector3CrossProduct(oy, az);
		_roll = angle(prj, ax, az);
	}

	if(trimf(1 - fabs(ax.y)) == 0){ // X轴是否与Y轴重合
		_pitch = 0;
	}else{
		GLKVector3 prj = GLKVector3CrossProduct(ax, oy);
		_pitch = angle(prj, az, ax);
	}

	if(trimf(1 - fabs(ay.x)) == 0){ // X轴是否与Y轴重合
		_yaw = 0;
	}else{
		// TODO:
		GLKVector3 prj = GLKVector3CrossProduct(ox, ay);
//		log_debug(@"ay: %f %f %f", ay.x, ay.y, ay.z);
//		log_debug(@"az: %f %f %f, prj: %f %f %f", az.x, az.y, az.z, prj.x, prj.y, prj.z);
		_yaw = angle(prj, az, ay);
	}

//	log_debug(@"%@", self);
}

- (void)subtract:(GEulerAngle *)right{
	_roll -= right.roll;
	_pitch -= right.pitch;
	_yaw -= right.yaw;
}

@end


static float angle(GLKVector3 vec0, GLKVector3 vec1, GLKVector3 direction){
	GLKVector3 cross = GLKVector3CrossProduct(vec0, vec1); // 算角度时的旋转轴
	float sign = GLKVector3DotProduct(direction, cross); // 旋转轴在方向轴上的投影
	float dot = GLKVector3DotProduct(vec0, vec1);
	// 避免计算误差导致符号发生重大改变
	//	log_debug(@"%.10f %.10f %.10f", sign, dot, FLT_EPSILON);
	sign = trimf(sign);
	dot = trimf(dot);
	//	log_debug(@"%f %f", sign, dot);
	float angle = atan2(copysign(GLKVector3Length(cross), sign), dot);
	return GLKMathRadiansToDegrees(angle);
}

static void quat_to_euler(GLKQuaternion q, float *roll, float *pitch, float *yaw, const char *mode){
	float r, p, y, w;
	float sinr, cosr, sinp, siny, cosy;
	float qs[3] = {q.x, q.y, q.z};
//	log_debug(@"quat: %.2f %.2f %.2f w: %.2f", q.x, q.y, q.z, q.w);
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
