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

- (void)rotateX:(float)degree{
	[self orbitX:degree y:_lookAt.y z:_lookAt.z];
}

// 相机绕Y轴的旋转比较特殊，始终保持相机与父坐标系Y轴的角度
- (void)rotateY:(float)degree{
	GLKMatrix4 mat = self.matrix;
	GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(mat);
	GLKQuaternion quat_i = GLKQuaternionInvert(quat);
	mat = GLKMatrix4Translate(mat, _lookAt.x, _lookAt.y, _lookAt.z);
	mat = GLKMatrix4Multiply(mat, GLKMatrix4MakeWithQuaternion(quat_i));
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Multiply(mat, GLKMatrix4MakeWithQuaternion(quat));
	mat = GLKMatrix4Translate(mat, -_lookAt.x, -_lookAt.y, -_lookAt.z);
	self.matrix = mat;
}

- (void)rotateZ:(float)degree{
	[self orbitZ:degree x:_lookAt.x y:_lookAt.y];
}

@end
