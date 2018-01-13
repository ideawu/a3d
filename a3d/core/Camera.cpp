//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Camera.h"

namespace a3d{
	Camera::Camera(float fovy, float width, float height, float depth){
		set(fovy, width, height, depth);
	}
	
	void Camera::set(float fovy, float width, float height, float depth){
		_fovy = fovy;
		_near = (height/2) / tan(GLKMathDegreesToRadians(fovy/2));
		_far = _near + depth;
		this->width(width);
		this->height(height);
		this->depth(depth);
	}
	
	void Camera::setup(){
		float width = this->width();
		float height = this->height();
		
		// 将近裁剪面设置为与viewport同大小
		_matrix3d = Matrix4(GLKMatrix4MakeFrustum(-width/2, width/2, -height/2, height/2, _near, _far));
		// 将前裁剪面后移，因为视点默认在 (0,0,0)，所以默认前裁剪面在(near,0,0)，这在旋转物体时不方便
		_matrix3d.translate(0, 0, -_near);
		// 翻转z轴，将z轴方向和人看屏幕方向相同
		_matrix3d.scale(1, 1, -1);
		// 将原点坐标移到屏幕右下角
		_matrix3d.translate(-width/2, -height/2, 0);
		
		_matrix2d = Matrix4(GLKMatrix4MakeOrtho(-width/2, width/2, -height/2, height/2, -_far, _far));
		// 翻转y轴，y轴方向向下
		_matrix2d.scale(1, -1, -1);
		// 将原点坐标移到屏幕左上角
		_matrix2d.translate(-width/2, -height/2, 0);
	}

	void Camera::setup(float width, float height){
		set(_fovy, width, height, this->depth());
		setup();
	}

	void Camera::setup(float width, float height, float depth){
		set(_fovy, width, height, depth);
		setup();
	}

	void Camera::setup(float fovy, float width, float height, float depth){
		set(fovy, width, height, depth);
		setup();
	}

}; // end namespace
