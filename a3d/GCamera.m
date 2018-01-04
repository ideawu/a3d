//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"

@interface GCamera(){
}
@property GObject *parent;
@end

@implementation GCamera

- (id)init{
	self = [super init];
	return self;
}

// 相机的世界坐标系 = matrix + angle.matrix
- (GLKMatrix4)matrix{
	GLKMatrix4 mat = super.matrix;
	if(_parent){
		mat = GLKMatrix4Multiply(mat, _parent.matrix);
	}
	mat = GLKMatrix4Multiply(mat, self.angle.matrix);
	return mat;
}

// 相机身体在世界（不是在被跟随物体中）坐标中的坐标系
- (GLKMatrix4)bodyMatrix{
	GLKMatrix4 mat = super.matrix;
	if(_parent){
		mat = GLKMatrix4Multiply(mat, _parent.matrix);
	}
	return mat;
}

#pragma mark - 目标跟随

- (void)follow:(GObject *)target{
	_parent = target;
	super.matrix = GLKMatrix4Multiply(super.matrix, GLKMatrix4Invert(_parent.matrix, NULL));
}

- (void)unfollow{
	super.matrix = self.bodyMatrix;
	_parent = nil;
}

// 相机的移动和移动比较特殊，以视线坐标为基准来移动
- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKMatrix4 mat1 = self.angle.matrix;
	GLKMatrix4 mat2 = GLKMatrix4Invert(mat1, NULL);
	super.matrix = GLKMatrix4Multiply(super.matrix, mat1);
	super.matrix = GLKMatrix4Translate(super.matrix, x, y, z);
	super.matrix = GLKMatrix4Multiply(super.matrix, mat2);
}

// 旋转时，以视角坐标为基准
- (void)rotateX:(float)degree{
	GLKMatrix4 mat1 = self.angle.matrix;
	GLKMatrix4 mat2 = GLKMatrix4Invert(mat1, NULL);
	super.matrix = GLKMatrix4Multiply(super.matrix, mat1);
	super.matrix = GLKMatrix4RotateX(super.matrix, GLKMathDegreesToRadians(degree));
	super.matrix = GLKMatrix4Multiply(super.matrix, mat2);
}

- (void)rotateZ:(float)degree{
	GLKMatrix4 mat1 = self.angle.matrix;
	GLKMatrix4 mat2 = GLKMatrix4Invert(mat1, NULL);
	super.matrix = GLKMatrix4Multiply(super.matrix, mat1);
	super.matrix = GLKMatrix4RotateZ(super.matrix, GLKMathDegreesToRadians(degree));
	super.matrix = GLKMatrix4Multiply(super.matrix, mat2);
}

// 相机绕Y轴的旋转比较特殊，始终保持相机与父坐标系Y轴的角度
- (void)rotateY:(float)degree{
	// p * -p * n * t * -n * p
	GLKMatrix4 mat = GLKMatrix4MakeTranslation(self.x, self.y, self.z); // Y轴坐标系
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -self.x, -self.y, -self.z); // 退出Y轴坐标系
	mat = GLKMatrix4Multiply(mat, self.bodyMatrix);
	super.matrix = mat;
}

@end
