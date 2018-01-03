//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"

@interface GCamera(){
}
@property GObject *target;
@property GLKMatrix4 targetOriginMatrix;
@end

@implementation GCamera

// 相机的移动和移动比较特殊，以视线坐标为基准来移动

- (void)moveX:(float)x y:(float)y z:(float)z{
	[super rotateZ:self.angle.z];
	[super rotateY:self.angle.y];
	[super rotateX:self.angle.x];
	
	[super moveX:x y:y z:z];
	
	[super rotateX:-self.angle.x];
	[super rotateY:-self.angle.y];
	[super rotateZ:-self.angle.z];
}

- (void)rotateX:(float)degree{
	[super rotateZ:self.angle.z];
	[super rotateY:self.angle.y];
	[super rotateX:self.angle.x];
	
	[super rotateX:degree];
	
	[super rotateX:-self.angle.x];
	[super rotateY:-self.angle.y];
	[super rotateZ:-self.angle.z];
}

// 相机绕Y轴的旋转比较特殊，始终保持相机与父坐标系Y轴的角度
- (void)rotateY:(float)degree{
	GVector3 *angle = self.angle;
	self.angle = [[GVector3 alloc] init];
	
	GLKMatrix4 mat = super.matrix;
	GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(mat);
	GLKQuaternion quat_i = GLKQuaternionInvert(quat);
	// 与旋转轴坐标系重合
	mat = GLKMatrix4Multiply(mat, GLKMatrix4MakeWithQuaternion(quat_i));
	// 旋转
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
	// 与旋转轴坐标系逆重合
	mat = GLKMatrix4Multiply(mat, GLKMatrix4MakeWithQuaternion(quat));
	self.matrix = mat;
	
	self.angle = angle;
}

- (void)rotateZ:(float)degree{
	[super rotateZ:self.angle.z];
	[super rotateY:self.angle.y];
	[super rotateX:self.angle.x];
	
	[super rotateZ:degree];
	
	[super rotateX:-self.angle.x];
	[super rotateY:-self.angle.y];
	[super rotateZ:-self.angle.z];
}

@end
