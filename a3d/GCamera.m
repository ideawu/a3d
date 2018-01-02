//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"

@interface GCamera(){
}
@end

@implementation GCamera

- (void)lookAtX:(float)x y:(float)y z:(float)z{
	_lookAt.x = x;
	_lookAt.y = y;
	_lookAt.z = z;
}

// 相机的旋转不同于物体旋转，物体旋转是以自身中点为准，相机旋转以自身坐标原点为准
- (void)rotateX:(float)degree{
	float x = _lookAt.x;
	float y = _lookAt.y;
	float z = _lookAt.z;
	[super moveX:x y:y z:z];
	[super rotateX:degree];
	[super moveX:-x y:-y z:-z];
}

// 相机绕Y轴的旋转比较特殊，始终保持相机与Y轴的角度
- (void)rotateY:(float)degree{
	GLKMatrix4 mat = self.matrix;
	GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(mat);
	GLKQuaternion quat_i = GLKQuaternionInvert(quat);
	mat = GLKMatrix4Translate(mat, -_lookAt.x, _lookAt.y, _lookAt.z);
	mat = GLKMatrix4Multiply(mat, GLKMatrix4MakeWithQuaternion(quat_i));
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Multiply(mat, GLKMatrix4MakeWithQuaternion(quat));
	mat = GLKMatrix4Translate(mat, -_lookAt.x, -_lookAt.y, -_lookAt.z);
	self.matrix = mat;
}

- (void)rotateZ:(float)degree{
	float x = _lookAt.x;
	float y = _lookAt.y;
	float z = _lookAt.z;
	[super moveX:x y:y z:z];
	[super rotateZ:degree];
	[super moveX:-x y:-y z:-z];
}

@end
