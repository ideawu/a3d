//  Created by ideawu on 08/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GMatrix4.h"

// 新坐标系原点在父坐标系中的位置，也即父坐标系内的任意点经过变换后，在父坐标系中的位置
//		vec4 = GLKMatrix4MultiplyVector4(matrix, vec4);
// 矩阵内的向量在父坐标内对应的向量
// 		vec3 = GLKMatrix4MultiplyVector3(matrix, vec);
// 父坐标系内的任意点，在新坐标系中的位置
//		pos = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(matrix), pos);
// 矩阵内的任意点，在父坐标系中的位置
//		pos = GLKMatrix4MultiplyVector4(matrix, pos);
// 获取旋转角度分量
//		GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(matrix);
// B做了A变换，结果就是B的新矩阵，也即A在世界中的矩阵。
//		GLKMatrix4Multiply(B, A);
// 将同一世界内的某坐标系移到另一坐标系内
//		GLKMatrix4Multiply(GLKMatrix4Invert(B), A);

// 欧拉角与四元数的转换：https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

@interface GMatrix4(){
}
@end


@implementation GMatrix4

- (id)init{
	self = [super init];
	_matrix = GLKMatrix4MakeTranslation(0, 0, 0);
	return self;
}

+ (GMatrix4 *)make{
	GMatrix4 *ret = [[GMatrix4 alloc] init];
	return ret;
}

- (GMatrix4 *)clone{
	GMatrix4 *ret = [[GMatrix4 alloc] init];
	[ret copy:self];
	return ret;
}

- (void)copy:(GMatrix4 *)src{
	self.matrix = src.matrix;
}

- (NSString *)description{
	NSMutableString *ret = [[NSMutableString alloc] initWithCapacity:256];
	[ret appendString:@"\n"];
	float *m = (float *)&_matrix;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			float v = m[i*4 + j];
			if(j == 3){
				[ret appendFormat:@"%.2f ", v];
			}else{
				[ret appendFormat:@"%6.2f ", v];
			}
		}
		[ret appendString:@"\n"];
	}
	return ret;
}

#pragma mark - 矩阵运算

- (void)invert{
	_matrix = GLKMatrix4Invert(_matrix, NULL);
}

- (void)enter:(GMatrix4 *)target{
	GMatrix4 *parent = [target clone];
	[parent invert];
	[self leftMultiply:parent];
}

- (void)leave:(GMatrix4 *)parent{
	[self leftMultiply:parent];
}

- (void)multiply:(GMatrix4 *)right{
	_matrix = GLKMatrix4Multiply(_matrix, right.matrix);
}

- (void)leftMultiply:(GMatrix4 *)left{
	_matrix = GLKMatrix4Multiply(left.matrix, _matrix);
}

- (GLKVector3)multiplyVector3:(GLKVector3)vec{
	return GLKMatrix4MultiplyVector3(_matrix, vec);
}

- (GLKVector4)multiplyVector4:(GLKVector4)vec{
	return GLKMatrix4MultiplyVector4(_matrix, vec);
}

#pragma mark - 矩阵在父坐标系中

//- (GLKMatrix4)matrix{
//	return _matrix;
//}

- (float)x{
	return _matrix.m30;
}

- (void)setX:(float)x{
	_matrix.m30 = x;
}

- (float)y{
	return _matrix.m31;
}

- (void)setY:(float)y{
	_matrix.m31 = y;
}

- (float)z{
	return _matrix.m32;
}

- (void)setZ:(float)z{
	_matrix.m32 = z;
}

- (GLKVector3)xAxis{
	return GLKMatrix4MultiplyVector3(_matrix, GLKVector3Make(1, 0, 0));
}

- (GLKVector3)yAxis{
	return GLKMatrix4MultiplyVector3(_matrix, GLKVector3Make(0, 1, 0));
}

- (GLKVector3)zAxis{
	return GLKMatrix4MultiplyVector3(_matrix, GLKVector3Make(0, 0, 1));
}

// X轴到父坐标系XZ平面的角度
- (float)xAngle{
	GLKVector3 v = self.xAxis;
	float sina = v.y;
	float cosa = v.x;
	return atan2(sina, cosa);
}

// Y轴到父坐标系XY平面的角度
- (float)yAngle{
	GLKVector3 v = self.yAxis;
	float sina = v.z;
	float cosa = v.y;
	return atan2(sina, cosa);
}

// Z轴到父坐标系YZ平面的角度
- (float)zAngle{
	GLKVector3 v = self.zAxis;
	float sina = v.x;
	float cosa = v.z;
	return atan2(sina, cosa);
}

- (void)resetXAngle{
	[self rotateZ:-self.xAngle];
}

- (void)resetYAngle{
	[self rotateY:-self.yAngle];
}

- (void)resetZAngle{
	[self rotateZ:-self.zAngle];
}

- (void)reset{
	_matrix = GLKMatrix4MakeTranslation(0, 0, 0);
}

- (void)resetTranslation{
	_matrix.m30 = 0;
	_matrix.m31 = 0;
	_matrix.m32 = 0;
}

- (void)resetRotation{
	GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(_matrix);
	GLKMatrix4 mat = GLKMatrix4MakeWithQuaternion(quat);
	mat = GLKMatrix4Invert(mat, NULL);
//	_matrix = GLKMatrix4Multiply(mat, _matrix);
	_matrix = GLKMatrix4Multiply(_matrix, mat);
}

#pragma mark - 矩阵自身的变换

- (void)scale:(float)ratio{
	_matrix = GLKMatrix4Scale(_matrix, ratio, ratio, ratio);
}

- (void)translateX:(float)x y:(float)y z:(float)z{
	[self moveX:x y:y z:z];
}

- (void)translateX:(float)distance{
	[self moveX:distance y:0 z:0];
}

- (void)translateY:(float)distance{
	[self moveX:0 y:distance z:0];
}

- (void)translateZ:(float)distance{
	[self moveX:0 y:0 z:distance];
}

- (void)moveX:(float)x y:(float)y z:(float)z{
	_matrix = GLKMatrix4Translate(_matrix, x, y, z);
}

- (void)moveX:(float)distance{
	[self moveX:distance y:0 z:0];
}

- (void)moveY:(float)distance{
	[self moveX:0 y:distance z:0];
}

- (void)moveZ:(float)distance{
	[self moveX:0 y:0 z:distance];
}

// 旋转的顺序有关系，此函数有歧义
//- (void)rotateX:(float)xDegree y:(float)yDegree z:(float)zDegree

- (void)rotateX:(float)degree{
	_matrix = GLKMatrix4RotateX(_matrix, GLKMathDegreesToRadians(degree));
}

- (void)rotateY:(float)degree{
	_matrix = GLKMatrix4RotateY(_matrix, GLKMathDegreesToRadians(degree));
}

- (void)rotateZ:(float)degree{
	_matrix = GLKMatrix4RotateZ(_matrix, GLKMathDegreesToRadians(degree));
}

- (void)rotate:(float)degree x:(float)x y:(float)y z:(float)z{
	_matrix = GLKMatrix4Rotate(_matrix, GLKMathDegreesToRadians(degree), x, y, z);
}

// 绕自身坐标系内的任意轴(p0->p1)旋转
- (void)orbit:(float)degree p0:(GLKVector3)p0 p1:(GLKVector3)p1{
	GLKVector3 vec = GLKVector3Subtract(p1, p0);
	_matrix = GLKMatrix4TranslateWithVector3(_matrix, p0);
	_matrix = GLKMatrix4RotateWithVector3(_matrix, GLKMathDegreesToRadians(degree), vec);
	_matrix = GLKMatrix4TranslateWithVector3(_matrix, GLKVector3Negate(p0));
}

- (void)orbitX:(float)degree y:(float)y z:(float)z{
	[self orbit:degree p0:GLKVector3Make(0, y, z) p1:GLKVector3Make(1, y, z)];
}

- (void)orbitY:(float)degree x:(float)x z:(float)z{
	[self orbit:degree p0:GLKVector3Make(x, 0, z) p1:GLKVector3Make(x, 1, z)];
}

- (void)orbitZ:(float)degree x:(float)x y:(float)y{
	[self orbit:degree p0:GLKVector3Make(x, y, 0) p1:GLKVector3Make(x, y, 1)];
}


// 消除超过某些精度的小数部分，避免如 -0.00001 这样的数影响符号位。
static float trimf(float f){
	return fabs(f)<FLT_EPSILON*10? 0 : f;
}

// 各轴按顺序做 -roll, -pitch, -yaw 之后，旋转分量将恢复
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
	
	//		log_debug(@"%f %f %f", r, p, y);
	//		log_debug(@"%f %f (%f) %f %f", sinr, cosr, sinp, siny, cosy);
	
	*roll = r;
	*pitch = p;
	*yaw = y;
}


@end
