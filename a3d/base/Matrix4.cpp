//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Matrix4.h"
#include "util.h"

namespace a3d{
	
	Matrix4::Matrix4(){
		_mat = GLKMatrix4Identity;
	}

//	Matrix4::Matrix4(const Matrix4 &mat){
//		_mat = mat._mat;
//	}

	Matrix4::Matrix4(const GLKMatrix4 &mat){
		_mat = mat;
	}
	
	Matrix4 Matrix4::identity(){
		return Matrix4();
	}

	Matrix4 Matrix4::frustum(float left, float right, float bottom, float top, float nearZ, float farZ){
		return Matrix4(GLKMatrix4MakeFrustum(left, right, bottom, top, nearZ, farZ));
	}
	
	Matrix4 Matrix4::ortho(float left, float right, float bottom, float top, float nearZ, float farZ){
		return Matrix4(GLKMatrix4MakeOrtho(left, right, bottom, top, nearZ, farZ));
	}

	const float* Matrix4::array() const{
		return (const float *)&_mat;
	}
	
	float Matrix4::x() const{
		return _mat.m30;
	}
	
	void Matrix4::x(float x){
		_mat.m30 = x;
	}

	float Matrix4::y() const{
		return _mat.m31;
	}
	
	void Matrix4::y(float y){
		_mat.m31 = y;
	}

	float Matrix4::z() const{
		return _mat.m32;
	}
	
	void Matrix4::z(float z){
		_mat.m32  = z;
	}

	void Matrix4::translate(float x, float y, float z){
		_mat = GLKMatrix4Translate(_mat, x, y, z);
	}
	
	void Matrix4::translate(const Vector3 &offset){
		this->translate(offset.x(), offset.y(), offset.z());
	}

	void Matrix4::rotateX(float degree){
		_mat = GLKMatrix4RotateX(_mat, degree_to_radian(degree));
	}
	
	void Matrix4::rotateY(float degree){
		_mat = GLKMatrix4RotateY(_mat, degree_to_radian(degree));
	}
	
	void Matrix4::rotateZ(float degree){
		_mat = GLKMatrix4RotateZ(_mat, degree_to_radian(degree));
	}
	
	void Matrix4::rotate(float degree, const Vector3 &vec){
		_mat = GLKMatrix4Rotate(_mat, degree_to_radian(degree), vec.x(), vec.y(), vec.z());
	}
	
	void Matrix4::rotate(float degree, const Axis &axis){
		this->translate(axis.origin);
		this->Matrix4::rotate(degree, axis.direction);
		this->translate(axis.origin.invert());
	}

	void Matrix4::scale(float xyz){
		this->scale(xyz, xyz, xyz);
	}

	void Matrix4::scale(float x, float y, float z){
		_mat = GLKMatrix4Scale(_mat, x, y, z);
	}
	
	Matrix4 Matrix4::invert() const{
		return Matrix4(GLKMatrix4Invert(_mat, NULL));
	}
	
	Matrix4 Matrix4::mul(const Matrix4 &mat) const{
		return Matrix4(GLKMatrix4Multiply(_mat, mat._mat));
	}
	
	Matrix4 Matrix4::div(const Matrix4 &mat) const{
		return this->mul(mat.invert());
	}
	
	Vector3 Matrix4::mulVector3(const Vector3 &vec) const{
		GLKVector3 v = GLKVector3Make(vec.x(), vec.y(), vec.z());
		v = GLKMatrix4MultiplyVector3WithTranslation(_mat, v);
		return Vector3(v.x, v.y, v.z);
	}

}; // end namespace
