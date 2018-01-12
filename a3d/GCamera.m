//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GCamera.h"
#import <OpenGL/gl.h>

@interface GCamera(){
	GLKVector3 _focus;
}
@property float near;
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

- (void)setup{
	float width = self.width;
	float height = self.height;
	self.near = (height/2) / tan(GLKMathDegreesToRadians(self.fovy/2));
	float far = self.near + self.depth;
	
	// 将前裁剪面设置为与viewport同大小
	_matrix3d = GLKMatrix4MakeFrustum(-width/2, width/2, -height/2, height/2, self.near, far);
	// 将前裁剪面后移，因为视点默认在 (0,0,0)，所以默认前裁剪面在(near,0,0)，这在旋转物体时不方便
	_matrix3d = GLKMatrix4Translate(_matrix3d, 0, 0, -self.near);
	// 翻转z轴，将z轴方向和人看屏幕方向相同
	_matrix3d = GLKMatrix4Scale(_matrix3d, 1, 1, -1);
	// 将原点坐标移到屏幕右下角
	_matrix3d = GLKMatrix4Translate(_matrix3d, -width/2, -height/2, 0);
	
	// OpenGL 的老方式
	//	glLoadIdentity();
	//	glFrustum(-width/2, width/2, -height/2, height/2, near, far);
	//	glTranslatef(0, 0, -near);
	//	glScalef(1, 1, -1);
	
	_matrix2d = GLKMatrix4MakeOrtho(-width/2, width/2, -height/2, height/2, -far, far);
	// 翻转y轴，y轴方向向下
	_matrix2d = GLKMatrix4Scale(_matrix2d, 1, -1, -1);
	// 将原点坐标移到屏幕左上角
	_matrix2d = GLKMatrix4Translate(_matrix2d, -width/2, -height/2, 0);
	
	glViewport(0, 0, width, height);
}

- (void)bind3D{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat *)&_matrix3d);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// 相机不是真正的物体，而是矩阵变换的记录。视野中的物体，将做与相机相反的变换。
	GLKMatrix4 matrix = GLKMatrix4Invert(self.matrix, NULL);
	glLoadMatrixf((const GLfloat *)&matrix);
	
	// 2D和3D用的属性一般不同，所以每一次都设置一遍
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	{
		glFrontFace(GL_CW); // 将顺时针方向多边形设为正表面，符合上右下左惯例顺序
	}
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, 0); // 清空纹理
	}
}

- (void)bind2D{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat *)&_matrix2d);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// 2D和3D用的属性一般不同，所以每一次都设置一遍
	glDisable(GL_MULTISAMPLE);
	//	glEnable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glEnable(GL_TEXTURE_2D);
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, 0); // 清空纹理
	}
}

- (GLKVector3)eye{
	float x = self.width/2;
	float y = self.height/2;
	return vec3(x, y, -self.near);
}

- (GRay *)rayFromScreenPointX:(float)x y:(float)y{
	GLKVector3 p1 = self.eye;
	GLKVector3 p2 = vec3(x, y, 0);
	p1 = mat4_mul_vec3(self.matrix, p1);
	p2 = mat4_mul_vec3(self.matrix, p2);
	GRay *ray = [GRay rayFrom:p1 to:p2];
	return ray;
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
