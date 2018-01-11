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
	GLKVector4 pos = GLKVector4Make(target.x, target.y, target.z, 1);
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
	
	GCamera *camera = [[GCamera alloc] init];
	camera.matrix = super.matrix;
//	camera.angle = 0; // 因为我们只旋转基座，所以视线先归零
	camera.center = self.center;
	[camera rotateY:targetAngle.yaw];
	[camera rotateX:targetAngle.pitch];
	return camera.matrix;
}

- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKVector4 p1 = GLKVector4Make(x, y, z, 1);
	p1 = GLKMatrix4MultiplyVector4(self.angle.matrix, p1); // 视线坐标转为基座坐标
	[super moveX:p1.x y:p1.y z:p1.z];
}

- (void)rotateX:(float)degree{
	GLKVector4 p0 = _center;
	GLKVector4 p1 = GLKVector4Make(p0.x+1, p0.y, p0.z, 1);
	p0 = GLKMatrix4MultiplyVector4(self.angle.matrix, p0); // 视线坐标转为基座坐标
	p1 = GLKMatrix4MultiplyVector4(self.angle.matrix, p1); // 视线坐标转为基座坐标
	[super orbit:degree p0:p0 p1:p1];
}

- (void)rotateZ:(float)degree{
	GLKVector4 p0 = _center;
	GLKVector4 p1 = GLKVector4Make(p0.x, p0.y, p0.z+1, 1);
	p0 = GLKMatrix4MultiplyVector4(self.angle.matrix, p0); // 视线坐标转为基座坐标
	p1 = GLKMatrix4MultiplyVector4(self.angle.matrix, p1); // 视线坐标转为基座坐标
	[super orbit:degree p0:p0 p1:p1];
}

// 相机平移到焦点处后，绕经过自身原点的父坐标Y轴的平行轴
- (void)rotateY:(float)degree{
	// 先求出旋转轴在世界标中
	GLKVector4 p0 = GLKMatrix4MultiplyVector4(self.matrix, _center);
	GLKVector4 p1 = GLKVector4Make(p0.x, p0.y+1, p0.z, 1);
	// 再将旋转轴放入相机基座坐标系
	p0 = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(super.matrix, NULL), p0);
	p1 = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(super.matrix, NULL), p1);
	[super orbit:degree p0:p0 p1:p1];
}

@end
