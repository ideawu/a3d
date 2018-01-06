//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"

@interface GCamera(){
	GObject *_target;
}
// 观察的焦点在相机坐标系内的位置，默认为相机原点
@property GLKVector3 center;
@end

@implementation GCamera

- (id)init{
	self = [super init];
	_center = GLKVector3Make(0, 0, 0);
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
//	GLKMatrix4 old = super.matrix;
//	if(_target){
//		super.matrix = GLKMatrix4Multiply(_target.matrix, super.matrix);
//	}
//	[self rotateX:self.angle.x y:self.angle.y z:self.angle.z];
//	GLKMatrix4 mat = super.matrix;
//	super.matrix = old;
//	return mat;
	GLKMatrix4 mat = super.matrix;
	if(_target){
		mat = GLKMatrix4Multiply(_target.matrix, mat);
	}
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

- (GObject *)target{
	return _target;
}

- (void)follow:(GObject *)target{
	if(_target){
		[self unfollow];
	}
	_target = target;
	// 跟随一个物体时，并不是将观察焦点移到目标身上，而是延z轴方向前移
	_center = GLKVector3Make(0, 0, target.z - self.z);
	log_debug(@"focus: %.2f %.2f %.2f", _center.x, _center.y, _center.z);
	// 将相机放入被跟随物体内
	super.matrix = GLKMatrix4Multiply(super.matrix, GLKMatrix4Invert(_target.matrix, NULL));
}

- (void)unfollow{
	if(_target){
		super.matrix = GLKMatrix4Multiply(_target.matrix, super.matrix);
		_center = GLKVector3Make(0, 0, 0);
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

// 相机平移到焦点处后绕自身X轴旋转
- (void)rotateX:(float)degree{
	GLKMatrix4 mat = super.matrix;
	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
	mat = GLKMatrix4RotateX(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
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

// 相机平移到焦点处后，绕经过自身原点的世界坐标Y轴的平行轴
- (void)rotateY:(float)degree{
	GLKMatrix4 mat1 = super.matrix;
	GLKMatrix4 mat2 = GLKMatrix4Invert(mat1, NULL);
	GLKVector3 axis = GLKVector3Make(0, 1, 0); // 世界Y轴
	axis = GLKMatrix4MultiplyVector3(mat2, axis); // 世界Y轴进入相机坐标系(移到相机原点)
	axis = GLKVector3Add(axis, _center); // 世界Y轴移到焦点
	
	GLKMatrix4 mat = super.matrix;
	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
	mat = GLKMatrix4RotateWithVector3(mat, GLKMathDegreesToRadians(degree), axis);
	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
	super.matrix = mat;

//	GLKMatrix4 mat;
//	mat = GLKMatrix4MakeTranslation(foc.x, foc.y, foc.z);
//	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
//	mat = GLKMatrix4Translate(mat, -foc.x, -foc.y, -foc.z);
////	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
//	mat = GLKMatrix4Multiply(mat, super.matrix);
//	super.matrix = mat;
//	foc = GLKMatrix4MultiplyVector3(super.matrix, _center);
//	log_debug(@"focus: %.2f %.2f %.2f", foc.x, foc.y, foc.z);
}

// 按相机特有的操作顺序，先后旋转 z-y-z 轴
- (void)rotateX:(float)x y:(float)y z:(float)z{
	[self rotateZ:z];
	[self rotateY:y];
	[self rotateX:x];
}

@end
