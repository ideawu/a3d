//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Camera.h"

namespace a3d{
	Camera* Camera::create(float fovy, float width, float height, float depth){
		Camera *ret = new Camera();
		ret->setup(fovy, width, height, depth);
		return ret;
	}
	
	void Camera::setup(float fovy, float width, float height, float depth){
		_fovy = fovy;
		_near = (fmax(width, height)/2) / tan(degree_to_radian(fovy/2));
		_far = _near + depth;
		this->width(width);
		this->height(height);
		this->depth(depth);
		
		// 将近裁剪面设置为与viewport同大小
		_matrix3D = Matrix4::frustum(-width/2, width/2, -height/2, height/2, _near, _far);
		// 将视点后移，这样前裁剪面z=0(只显示z>0的物体)
		_matrix3D.translate(0, 0, -_near);
		// -0.0001，这样也显示z=0的物体
		_matrix3D.translate(0, 0, -0.0001);
		// 翻转z轴，将z轴方向和人看屏幕方向相同
		_matrix3D.scale(1, 1, -1);

		_matrix2D = Matrix4::ortho(-width/2, width/2, -height/2, height/2, -_far, _far);
		_matrix3D.translate(0, 0, -0.0001);
		// 翻转y,z轴，y轴方向向下
		_matrix2D.scale(1, -1, -1);
		// 将原点坐标移到屏幕左上角
		_matrix2D.translate(-width/2, -height/2, 0);
	}

	Matrix4 Camera::matrix3D() const{
		// 视野中的物体，将做与相机相反的运动
		Matrix4 mat = _matrix3D.mul(this->matrix().invert());
		return mat;
	}

	Matrix4 Camera::matrix2D() const{
		return _matrix2D;
	}
	
}; // end namespace

// - (void)moveX:(float)x y:(float)y z:(float)z{
// GLKVector3 p1 = vec3(x, y, z);
// p1 = mat4_mul_vec3(self.angle.matrix, p1); // 视线坐标转为基座坐标
// [super moveX:p1.x y:p1.y z:p1.z];
// }
// 
// - (void)rotateX:(float)degree{
// GLKVector3 p0 = self.focus;
// GLKVector3 p1 = vec3(p0.x+1, p0.y, p0.z);
// p0 = mat4_mul_vec3(self.angle.matrix, p0); // 视线坐标转为基座坐标
// p1 = mat4_mul_vec3(self.angle.matrix, p1); // 视线坐标转为基座坐标
// [super orbit:degree p0:p0 p1:p1];
// }
// 
// - (void)rotateZ:(float)degree{
// GLKVector3 p0 = self.focus;
// GLKVector3 p1 = vec3(p0.x, p0.y, p0.z+1);
// p0 = mat4_mul_vec3(self.angle.matrix, p0); // 视线坐标转为基座坐标
// p1 = mat4_mul_vec3(self.angle.matrix, p1); // 视线坐标转为基座坐标
// [super orbit:degree p0:p0 p1:p1];
// }
// 
// // 相机平移到焦点处后，绕经过自身原点的父坐标Y轴的平行轴
// - (void)rotateY:(float)degree{
// // 先求出旋转轴在世界标中
// GLKVector3 p0 = mat4_mul_vec3(self.matrix, self.focus);
// GLKVector3 p1 = vec3(p0.x, p0.y+1, p0.z);
// // 再将旋转轴放入相机基座坐标系
// p0 = mat4_mul_vec3(mat4_invert(super.matrix), p0);
// p1 = mat4_mul_vec3(mat4_invert(super.matrix), p1);
// [super orbit:degree p0:p0 p1:p1];
// }

