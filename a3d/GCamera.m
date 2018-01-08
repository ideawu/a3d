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
@property GLKVector4 center;
@end

@implementation GCamera

- (id)init{
	self = [super init];
	_center = GLKVector4Make(0, 0, 0, 1); // TODO
	return self;
}

- (GCamera *)clone{
	GCamera *ret = [[GCamera alloc] init];
	ret.matrix = super.matrix;
	ret.center = _center;
	return ret;
}

- (GLKMatrix4)matrix{
	if(_follow){
		GMatrix4 *mat = [_follow.shadow clone];
		[mat leave:_follow.target];
		return mat.matrix;
	}
	return super.matrix;
}

#pragma mark - 目标跟随

- (GMatrix4 *)target{
	return _follow.target;
}

// 跟随有几种模式：位移，X，Y，Z各轴旋转的跟随应该单独可配。
- (void)follow:(GObject *)target{
	if(_follow){
		[self unfollow];
	}
	GLKVector4 pos = GLKVector4Make(target.x, target.y, target.z, 1);
	_center = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(self.matrix, NULL), pos);
	_follow = [[GFollow alloc] init];
	_follow.target = target;
	_follow.shadow = [self clone];
	[_follow.shadow enter:_follow.target];
//	log_debug(@"target: %f %f %f", target.x, target.y, target.z);
//	log_debug(@"self: %f %f %f", self.x, self.y, self.z);
}

- (void)unfollow{
	if(_follow){
		super.matrix = self.matrix;
		_center = GLKVector4Make(0, 0, 0, 1);
	}
	_follow = nil;
}

// 相机的移动以视线坐标为基准来移动
- (void)moveX:(float)x y:(float)y z:(float)z{
	// 先将视线坐标中的位移对应到世界坐标中的位移
	GLKMatrix4 mat = GLKMatrix4Invert(self.matrix, NULL);
	GLKVector4 v0 = GLKMatrix4MultiplyVector4(mat, GLKVector4Make(0, 0, 0, 1));
	GLKVector4 v1 = GLKMatrix4MultiplyVector4(mat, GLKVector4Make(x, y, z, 1));
	v1 = GLKVector4Subtract(v1, v0);
	self.x += v1.x;
	self.y += v1.y;
	self.z += v1.z;
}

- (void)rotateX:(float)degree{
	[super moveX:_center.x y:_center.y z:_center.z];
	[super rotateX:degree];
	[super moveX:-_center.x y:-_center.y z:-_center.z];
}

- (void)rotateZ:(float)degree{
	[super moveX:_center.x y:_center.y z:_center.z];
	[super rotateZ:degree];
	[super moveX:-_center.x y:-_center.y z:-_center.z];
}

// 相机平移到焦点处后，绕经过自身原点的世界坐标Y轴的平行轴
- (void)rotateY:(float)degree{
//	GLKMatrix4 mat = super.matrix;
//	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
//	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
//	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
//	super.matrix = mat;

//	GLKMatrix4 mat = super.matrix;
//	GLKVector4 axis = GLKVector4Make(0, 1, 0, 1); // 世界Y轴
//	axis = GLKMatrix4MultiplyVector3(GLKMatrix4Invert(mat, NULL), axis); // 世界Y轴进入相机坐标系(移到相机原点)
//	mat = GLKMatrix4Translate(mat, _center.x, _center.y, _center.z);
//	mat = GLKMatrix4RotateWithVector3(mat, GLKMathDegreesToRadians(degree), axis);
//	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
//	super.matrix = mat;
	
	// P * -P * N * T * -N * P

	GLKMatrix4 mat = GLKMatrix4MakeTranslation(_center.x, _center.y, _center.z);
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -_center.x, -_center.y, -_center.z);
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
