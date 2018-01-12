//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"

@interface GCamera(){
	GLKVector3 _focus;
}
@end

@implementation GCamera

- (id)init{
	self = [super init];
	_focus = GLKVector3Make(0, 0, 0);
	return self;
}

- (GLKMatrix4)matrix{
	GLKMatrix4 mat = self.angle.matrix;
	if(_follow){
		mat = mat4_mul(self.followMatrix, mat);
	}else{
		mat = mat4_mul(super.matrix, mat);
	}
	return mat;
}

#pragma mark - 目标跟随

- (void)follow:(GMatrix4 *)target{
	if(_follow){
		[self unfollow];
	}
	_follow = [GFollow followTarget:target];
}

- (void)unfollow{
	if(_follow){
		super.matrix = self.followMatrix;
		_follow = nil;
	}
}

- (GLKMatrix4)followMatrix{
	GEulerAngle *originAngle = [GEulerAngle angleWithMatrix:_follow.origin];
	GEulerAngle *targetAngle = [GEulerAngle angleWithMatrix:_follow.target];
	[targetAngle subtract:originAngle];
	
	float x = _follow.target.x - _follow.origin.x;
	float y = _follow.target.y - _follow.origin.y;
	float z = _follow.target.z - _follow.origin.z;

	// 只旋转基座
	GCamera *camera = [[GCamera alloc] init];
	camera.matrix = super.matrix;
	camera.focus = self.focus;
	[camera rotateY:targetAngle.yaw];
	[camera rotateX:targetAngle.pitch];
	
	GLKMatrix4 mat = mat4(x, y, z);
	mat = mat4_mul(mat, camera.matrix);
	return mat;
}

- (GLKVector3)focus{
	if(_follow){
		GLKVector3 pos = _follow.target.pos;
		pos = mat4_mul_vec3(mat4_invert(super.matrix), pos);
		return pos;
	}else{
		return _focus;
	}
}

- (void)setFocus:(GLKVector3)focus{
	_focus = focus;
}

- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKVector3 p1 = vec3(x, y, z);
	p1 = mat4_mul_vec3(self.angle.matrix, p1); // 视线坐标转为基座坐标
	[super moveX:p1.x y:p1.y z:p1.z];
}

- (void)rotateX:(float)degree{
	GLKVector3 p0 = self.focus;
	GLKVector3 p1 = vec3(p0.x+1, p0.y, p0.z);
	p0 = mat4_mul_vec3(self.angle.matrix, p0); // 视线坐标转为基座坐标
	p1 = mat4_mul_vec3(self.angle.matrix, p1); // 视线坐标转为基座坐标
	[super orbit:degree p0:p0 p1:p1];
}

- (void)rotateZ:(float)degree{
	GLKVector3 p0 = self.focus;
	GLKVector3 p1 = vec3(p0.x, p0.y, p0.z+1);
	p0 = mat4_mul_vec3(self.angle.matrix, p0); // 视线坐标转为基座坐标
	p1 = mat4_mul_vec3(self.angle.matrix, p1); // 视线坐标转为基座坐标
	[super orbit:degree p0:p0 p1:p1];
}

// 相机平移到焦点处后，绕经过自身原点的父坐标Y轴的平行轴
- (void)rotateY:(float)degree{
	// 先求出旋转轴在世界标中
	GLKVector3 p0 = mat4_mul_vec3(self.matrix, self.focus);
	GLKVector3 p1 = vec3(p0.x, p0.y+1, p0.z);
	// 再将旋转轴放入相机基座坐标系
	p0 = mat4_mul_vec3(mat4_invert(super.matrix), p0);
	p1 = mat4_mul_vec3(mat4_invert(super.matrix), p1);
	[super orbit:degree p0:p0 p1:p1];
}

@end
