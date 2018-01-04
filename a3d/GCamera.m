//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"

@interface GCamera(){
}
@end

@implementation GCamera

- (id)init{
	self = [super init];
	return self;
}

- (GLKMatrix4)matrix{
	GLKMatrix4 mat = super.matrix;
	mat = GLKMatrix4Multiply(mat, self.angle.matrix);
	return mat;
}

// 相机的移动和移动比较特殊，以视线坐标为基准来移动
- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKMatrix4 mat1 = self.angle.matrix;
	GLKMatrix4 mat2 = GLKMatrix4Invert(mat1, NULL);
	super.localMatrix = GLKMatrix4Multiply(super.localMatrix, mat1);
	super.localMatrix = GLKMatrix4Translate(super.localMatrix, x, y, z);
	super.localMatrix = GLKMatrix4Multiply(super.localMatrix, mat2);
}

- (void)rotateX:(float)degree{
	GLKMatrix4 mat1 = self.angle.matrix;
	GLKMatrix4 mat2 = GLKMatrix4Invert(mat1, NULL);
	super.localMatrix = GLKMatrix4Multiply(super.localMatrix, mat1);
	super.localMatrix = GLKMatrix4RotateX(super.localMatrix, GLKMathDegreesToRadians(degree));
	super.localMatrix = GLKMatrix4Multiply(super.localMatrix, mat2);
}

- (void)rotateZ:(float)degree{
	GLKMatrix4 mat1 = self.angle.matrix;
	GLKMatrix4 mat2 = GLKMatrix4Invert(mat1, NULL);
	super.localMatrix = GLKMatrix4Multiply(super.localMatrix, mat1);
	super.localMatrix = GLKMatrix4RotateZ(super.localMatrix, GLKMathDegreesToRadians(degree));
	super.localMatrix = GLKMatrix4Multiply(super.localMatrix, mat2);
}

// 相机绕Y轴的旋转比较特殊，始终保持相机与父坐标系Y轴的角度
- (void)rotateY:(float)degree{
	// p * -p * n * t * -n * p
	GLKMatrix4 mat = GLKMatrix4MakeTranslation(self.x, self.y, self.z); // Y轴坐标系
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -self.x, -self.y, -self.z); // 退出Y轴坐标系
	mat = GLKMatrix4Multiply(mat, self.localMatrix);
	super.localMatrix = mat;
}

@end
