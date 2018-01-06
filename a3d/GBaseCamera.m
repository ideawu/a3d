//  Created by ideawu on 06/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GBaseCamera.h"

@interface GBaseCamera(){
}
@end


@implementation GBaseCamera

- (id)init{
	self = [super init];
	_center = GLKVector3Make(0, 0, 100); // TODO
	return self;
}

// 相机的移动以视线坐标为基准来移动
- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKMatrix4 mat = self.matrix;
	mat = GLKMatrix4Translate(mat, x, y, z);
	super.matrix = mat;
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
	GLKMatrix4 mat = super.matrix;
	GLKVector3 axis = GLKVector3Make(0, 1, 0); // 世界Y轴
	axis = GLKMatrix4MultiplyVector3(GLKMatrix4Invert(mat, NULL), axis); // 世界Y轴进入相机坐标系(移到相机原点)
	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
	mat = GLKMatrix4RotateWithVector3(mat, GLKMathDegreesToRadians(degree), axis);
	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
	super.matrix = mat;
}

@end
