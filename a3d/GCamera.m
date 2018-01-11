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
	_center = GLKVector4Make(0, 0, 0, 1);
	return self;
}

- (GLKMatrix4)matrix{
	GLKMatrix4 mat = self.angle.matrix;
	if(_follow){
		mat = GLKMatrix4Multiply(self.followMatrix, mat);
	}else{
		mat = GLKMatrix4Multiply(super.matrix, mat);
	}
	return mat;
}

#pragma mark - 目标跟随

- (void)follow:(GMatrix4 *)target{
	if(_follow){
		[self unfollow];
	}
	GLKVector4 pos = target.pos;
	_center = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(super.matrix, NULL), pos);
	_follow = [GFollow followTarget:target];
}

- (void)unfollow{
	if(_follow){
		super.matrix = self.followMatrix;
		_follow = nil;
		_center = GLKVector4Make(0, 0, 0, 1);
	}
}

- (GLKMatrix4)followMatrix{
	GEulerAngle *originAngle = [GEulerAngle angleWithMatrix:_follow.origin];
	GEulerAngle *targetAngle = [GEulerAngle angleWithMatrix:_follow.target];
	[targetAngle subtract:originAngle];
	
	float x = _follow.target.x - _follow.origin.x;
	float y = _follow.target.y - _follow.origin.y;
	float z = _follow.target.z - _follow.origin.z;

	GCamera *camera = [[GCamera alloc] init];
	// 只旋转基座
	camera.matrix = super.matrix;
	camera.center = self.focus;
	[camera rotateY:targetAngle.roll];
	[camera rotateX:targetAngle.yaw];
	
	GLKMatrix4 mat = GLKMatrix4MakeTranslation(x, y, z);
	mat = GLKMatrix4Multiply(mat, camera.matrix);
	return mat;
}

- (GLKVector4)focus{
	if(_follow){
		GLKVector4 pos = _follow.target.pos;
		pos = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(super.matrix, NULL), pos);
		return pos;
	}else{
		return _center;
	}
}

- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKVector4 p1 = GLKVector4Make(x, y, z, 1);
	p1 = GLKMatrix4MultiplyVector4(self.angle.matrix, p1); // 视线坐标转为基座坐标
	[super moveX:p1.x y:p1.y z:p1.z];
}

- (void)rotateX:(float)degree{
	GLKVector4 p0 = self.focus;
	GLKVector4 p1 = GLKVector4Make(p0.x+1, p0.y, p0.z, 1);
	p0 = GLKMatrix4MultiplyVector4(self.angle.matrix, p0); // 视线坐标转为基座坐标
	p1 = GLKMatrix4MultiplyVector4(self.angle.matrix, p1); // 视线坐标转为基座坐标
	[super orbit:degree p0:p0 p1:p1];
}

- (void)rotateZ:(float)degree{
	GLKVector4 p0 = self.focus;
	GLKVector4 p1 = GLKVector4Make(p0.x, p0.y, p0.z+1, 1);
	p0 = GLKMatrix4MultiplyVector4(self.angle.matrix, p0); // 视线坐标转为基座坐标
	p1 = GLKMatrix4MultiplyVector4(self.angle.matrix, p1); // 视线坐标转为基座坐标
	[super orbit:degree p0:p0 p1:p1];
}

// 相机平移到焦点处后，绕经过自身原点的父坐标Y轴的平行轴
- (void)rotateY:(float)degree{
	// 先求出旋转轴在世界标中
	GLKVector4 p0 = GLKMatrix4MultiplyVector4(self.matrix, self.focus);
	GLKVector4 p1 = GLKVector4Make(p0.x, p0.y+1, p0.z, 1);
	// 再将旋转轴放入相机基座坐标系
	p0 = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(super.matrix, NULL), p0);
	p1 = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(super.matrix, NULL), p1);
	[super orbit:degree p0:p0 p1:p1];
}

@end
