//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"

// 注意：对于相机来说，视线的横向转动，并不是绕着相机自身的Y轴转动，
// 而是绕着其所观察的世界的Y轴进行转动，这样，视线横扫时可以始终保持相机与地面的固定角度。

@interface GCamera(){
}
@property GObject *target;
@end

@implementation GCamera

- (id)init{
	self = [super init];
	return self;
}

- (GLKMatrix4)eyeMatrix{
	GLKVector3 vec0 = GLKVector3Make(0, 1, 0);
	GLKVector3 vec1 = GLKMatrix4MultiplyVector3(super.matrix, vec0);
	float dp = GLKVector3DotProduct(vec0, vec1);
	float rad = acos(dp);
	GLKMatrix4 mat = GLKMatrix4MakeTranslation(0, 0, 0);
	mat = GLKMatrix4RotateZ(mat, GLKMathDegreesToRadians(self.angle.z));
	mat = GLKMatrix4RotateX(mat, -rad);
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(self.angle.y));
	mat = GLKMatrix4RotateX(mat, rad);
	mat = GLKMatrix4RotateX(mat, GLKMathDegreesToRadians(self.angle.x));
	return mat;
}

- (GLKMatrix4)matrix{
	GLKMatrix4 old = super.matrix;
	if(_target){
		super.matrix = GLKMatrix4Multiply(_target.matrix, super.matrix);
	}
	[self rotateX:self.angle.x y:self.angle.y z:self.angle.z];
	GLKMatrix4 mat = super.matrix;
	super.matrix = old;
	return mat;
}

// 基座在世界坐标中的矩阵
- (GLKMatrix4)bodyMatrix{
	GLKMatrix4 mat = super.matrix;
	if(_target){
		mat = GLKMatrix4Multiply(_target.matrix, mat);
	}
	return mat;
}

#pragma mark - 目标跟随

- (void)follow:(GObject *)target{
	_target = target;
	super.matrix = GLKMatrix4Multiply(super.matrix, GLKMatrix4Invert(_target.matrix, NULL));
}

- (void)unfollow{
	if(_target){
		super.matrix = GLKMatrix4Multiply(_target.matrix, super.matrix);
	}
	_target = nil;
}

// 相机的移动以视线坐标为基准来移动
- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKMatrix4 mat1 = self.matrix;
	GLKMatrix4 mat2 = GLKMatrix4Translate(mat1, x, y, z);
	GLKMatrix4 mat3 = GLKMatrix4Subtract(mat2, mat1);
	super.matrix = GLKMatrix4Add(super.matrix, mat3);
}

// X 轴旋转以基座为基准
- (void)rotateX:(float)degree{
	GLKMatrix4 mat = super.matrix;
//	if(_target){
//		// 回到世界中(从目标脱离)
//		mat = GLKMatrix4Multiply(_target.matrix, mat);
//	}
	// 转动
	mat = GLKMatrix4RotateX(mat, GLKMathDegreesToRadians(degree));
//	if(_target){
//		// 回到被跟随目标中
//		mat = GLKMatrix4Multiply(mat, GLKMatrix4Invert(_target.matrix, NULL));
//	}
	super.matrix = mat;
}

// Z 轴旋转以基座为基准
- (void)rotateZ:(float)degree{
	super.matrix = GLKMatrix4RotateY(super.matrix, GLKMathDegreesToRadians(degree));
}

// 相机绕Y轴的旋转比较特殊，始终保持相机基座与父坐标系Y轴的角度
- (void)rotateY:(float)degree{
	// p * -p * n * t * -n * p
	GLKMatrix4 mat = GLKMatrix4MakeTranslation(self.x, self.y, self.z); // Y轴坐标系
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -self.x, -self.y, -self.z); // 退出Y轴坐标系
	mat = GLKMatrix4Multiply(mat, super.matrix);
	super.matrix = mat;
}

// 按相机特有的操作顺序，先后旋转 z-y-z 轴
- (void)rotateX:(float)x y:(float)y z:(float)z{
	[self rotateZ:z];
	[self rotateY:y];
	[self rotateX:x];
}

@end
