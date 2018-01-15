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
	
	Matrix4 Camera::matrix3D() const{
		// 视野中的物体，将做与相机相反的变换。
		return _matrix3D.mul(this->invert());
	}
	
	Matrix4 Camera::matrix2D() const{
		return _matrix2D;
	}
	
	void Camera::setup(float fovy, float width, float height, float depth){
		_fovy = fovy;
		_near = (height/2) / tan(GLKMathDegreesToRadians(fovy/2));
		_far = _near + depth;
		this->width(width);
		this->height(height);
		this->depth(depth);
		
		// 将近裁剪面设置为与viewport同大小
		_matrix3D = Matrix4(GLKMatrix4MakeFrustum(-width/2, width/2, -height/2, height/2, _near, _far));
		// 将前裁剪面后移，因为视点默认在 (0,0,0)，所以默认前裁剪面在(near,0,0)，这在旋转物体时不方便
		_matrix3D.translate(0, 0, -_near-0.01);
//		// 翻转z轴，将z轴方向和人看屏幕方向相同
//		_matrix3D.scale(1, 1, -1);
		// 将原点坐标移到屏幕右下角
		_matrix3D.translate(-width/2, -height/2, 0);

		_matrix2D = Matrix4(GLKMatrix4MakeOrtho(-width/2, width/2, -height/2, height/2, -_far, _far));
		// 翻转y轴，y轴方向向下
		_matrix2D.scale(1, -1, -1);
		// 将原点坐标移到屏幕左上角
		_matrix2D.translate(-width/2, -height/2, 0);
	}

}; // end namespace
