//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"
#import "GFollow.h"

@interface GCamera(){
	GObject *_target;
	GFollow *_follow;
}
// 观察的焦点在相机坐标系内的位置，默认为相机原点
@property GLKVector3 center;
@end

@implementation GCamera

- (id)init{
	self = [super init];
	_center = GLKVector3Make(0, 0, 500); // TODO
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
	GLKMatrix4 mat = super.matrix;
	if(_follow){
		mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
//		mat = GLKMatrix4Multiply(_follow.matrix, mat);
		mat = GLKMatrix4Multiply(mat, _follow.matrix);
		mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
	}
	return mat;
}

#pragma mark - 目标跟随

- (GObject *)target{
//	return _target;
	return _follow.target;
}

// 跟随有几种模式：位移，X，Y，Z各轴旋转的跟随应该单独可配。
- (void)follow:(GObject *)target{
	if(_follow){
		[self unfollow];
	}
	_follow = [[GFollow alloc] init];
	_follow.target = target;
	_center = GLKVector3Make(target.x - super.x, target.y - super.y, target.z - super.z);
//	_center = GLKVector3Make(0, 0, target.z - super.z);
	log_debug(@"%f %f %f", _center.x, _center.y, _center.z);
}

- (void)unfollow{
	if(_follow){
		GLKMatrix4 mat = super.matrix;
		mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
		mat = GLKMatrix4Multiply(_follow.matrix, mat);
		mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
		super.matrix = mat;
//		_center = GLKVector3Make(0, 0, 0);
	}
	_follow = nil;
}

// 相机的移动以视线坐标为基准来移动
- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKMatrix4 mat = self.matrix;
	if(_target){
		mat = GLKMatrix4Multiply(_target.matrix, mat);
	}
	mat = GLKMatrix4Translate(mat, x, y, z);
	if(_target){
		mat = GLKMatrix4Multiply(GLKMatrix4Invert(_target.matrix, NULL), mat);
	}
	super.matrix = mat;
}

// 相机平移到焦点处后绕自身X轴旋转
- (void)rotateX:(float)degree{
	GLKMatrix4 mat = super.matrix;
	if(_target){
		mat = GLKMatrix4Multiply(_target.matrix, mat);
	}

	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
	mat = GLKMatrix4RotateX(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);

	if(_target){
		mat = GLKMatrix4Multiply(GLKMatrix4Invert(_target.matrix, NULL), mat);
	}
	super.matrix = mat;
}

// 相机平移到焦点处后，绕经过自身原点的世界坐标Y轴的平行轴
- (void)rotateY:(float)degree{
	GLKMatrix4 mat = super.matrix;
	if(_target){
		mat = GLKMatrix4Multiply(_target.matrix, mat);
	}
	
	GLKVector3 axis = GLKVector3Make(0, 1, 0); // 世界Y轴
	axis = GLKMatrix4MultiplyVector3(GLKMatrix4Invert(mat, NULL), axis); // 世界Y轴进入相机坐标系(移到相机原点)
	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
	mat = GLKMatrix4RotateWithVector3(mat, GLKMathDegreesToRadians(degree), axis);
	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);

	if(_target){
		mat = GLKMatrix4Multiply(GLKMatrix4Invert(_target.matrix, NULL), mat);
	}
	super.matrix = mat;
}

// 相机平移到焦点处后绕自身Z轴旋转
- (void)rotateZ:(float)degree{
	GLKMatrix4 mat = super.matrix;
	if(_target){
		mat = GLKMatrix4Multiply(_target.matrix, mat);
	}
	
	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
	mat = GLKMatrix4RotateZ(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
	
	if(_target){
		mat = GLKMatrix4Multiply(GLKMatrix4Invert(_target.matrix, NULL), mat);
	}
	super.matrix = mat;
}

// 按相机特有的操作顺序，先后旋转 z-y-z 轴
- (void)rotateX:(float)x y:(float)y z:(float)z{
	[self rotateZ:z];
	[self rotateY:y];
	[self rotateX:x];
}

@end
