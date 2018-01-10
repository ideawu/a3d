//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"

@interface GCamera(){
}
@property GMatrix4 *target;
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
	ret.target = _target;
	ret.center = _center;
	return ret;
}

- (GLKMatrix4)matrix{
	GLKMatrix4 mat = super.matrix;
	if(_target){
		mat = GLKMatrix4Multiply(_target.matrix, mat);
	}
	return mat;
}

#pragma mark - 目标跟随

- (void)follow:(GMatrix4 *)target{
	if(_target){
		[self unfollow];
	}
	[self enter:target];
	_target = target;
	GLKVector4 pos = GLKVector4Make(0, 0, 0, 1); // 相机盯着父坐标的原点
	_center = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(super.matrix, NULL), pos);
}

- (void)unfollow{
	if(_target){
		[self leave:_target];
		_target = nil;
		_center = GLKVector4Make(0, 0, 0, 1);
	}
}

// 相机的移动以视线坐标为基准，且在世界中移动
- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKMatrix4 mat = self.matrix;
	GLKVector4 v0 = GLKMatrix4MultiplyVector4(mat, GLKVector4Make(0, 0, 0, 1));
	GLKVector4 v1 = GLKMatrix4MultiplyVector4(mat, GLKVector4Make(x, y, z, 1));
	v1 = GLKVector4Subtract(v1, v0);
	self.x += v1.x;
	self.y += v1.y;
	self.z += v1.z;
}

- (void)rotateX:(float)degree{
	GLKVector4 focus = [self focus];
	[super moveX:focus.x y:focus.y z:focus.z];
	[super rotateX:degree];
	[super moveX:-focus.x y:-focus.y z:-focus.z];
}

- (void)rotateZ:(float)degree{
	GLKVector4 focus = [self focus];
	[super moveX:focus.x y:focus.y z:focus.z];
	[super rotateZ:degree];
	[super moveX:-focus.x y:-focus.y z:-focus.z];
}

- (GLKVector4)focus{
	if(_target){
		return GLKMatrix4MultiplyVector4(GLKMatrix4Invert(super.matrix, NULL), GLKVector4Make(0, 0, 0, 1));
	}else{
		return _center;
	}
}

// 相机平移到焦点处后，绕经过自身原点的父坐标Y轴的平行轴
- (void)rotateY:(float)degree{
	// P * -P * N * T * -N * P
	GLKVector4 focus = [self focus];
	GLKVector3 p0 = GLKVector3Make(focus.x, focus.y, focus.z);
	GLKVector3 p1 = GLKVector3Make(0, 1, 0);
	// 旋转点在世界中
	p1 = GLKMatrix4MultiplyVector3(GLKMatrix4Invert(self.matrix, NULL), p1);
	p1 = GLKVector3Add(p1, p0);
//	log_debug(@"(%f %f %f)->(%f %f %f)", p0.x, p0.y, p0.z, p1.x, p1.y, p1.z);
	[super orbit:degree p0:p0 p1:p1];
}

@end
