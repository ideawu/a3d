//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Matrix4.h"

namespace a3d{
	
	Matrix4::Matrix4(){
		_mat = GLKMatrix4Identity;
	}

	Matrix4::Matrix4(const Matrix4 &mat){
		_mat = mat._mat;
	}

	Matrix4::Matrix4(GLKMatrix4 mat){
		_mat = mat;
	}
	
	Matrix4 Matrix4::identity(){
		return Matrix4();
	}

	const float* Matrix4::matrix() const{
		return (const float *)&_mat;
	}

	Vector3 Matrix4::pos() const{
		return Vector3(x(), y(), z());
	}
	
	float Matrix4::x() const{
		return _mat.m30;
	}
	
	float Matrix4::y() const{
		return _mat.m31;
	}
	
	float Matrix4::z() const{
		return _mat.m32;
	}
	
	void Matrix4::translate(float x, float y, float z){
		_mat = GLKMatrix4Translate(_mat, x, y, z);
	}
	
	void Matrix4::translate(Vector3 offset){
		this->translate(offset.x(), offset.y(), offset.z());
	}

	void Matrix4::rotateX(float degree){
		_mat = GLKMatrix4RotateX(_mat, GLKMathDegreesToRadians(degree));
	}
	
	void Matrix4::rotateY(float degree){
		_mat = GLKMatrix4RotateY(_mat, GLKMathDegreesToRadians(degree));
	}
	
	void Matrix4::rotateZ(float degree){
		_mat = GLKMatrix4RotateZ(_mat, GLKMathDegreesToRadians(degree));
	}
	
	void Matrix4::rotate(float degree, Vector3 vec){
		_mat = GLKMatrix4Rotate(_mat, GLKMathDegreesToRadians(degree), vec.x(), vec.y(), vec.z());
	}
	
	void Matrix4::rotate(float degree, const Axis &axis){
		this->translate(axis.origin);
		this->Matrix4::rotate(degree, axis.direction);
		this->translate(axis.origin.invert());
	}

	void Matrix4::scale(float x, float y, float z){
		_mat = GLKMatrix4Scale(_mat, x, y, z);
	}
	
	Matrix4 Matrix4::invert() const{
		return Matrix4(GLKMatrix4Invert(_mat, NULL));
	}

	Matrix4 Matrix4::add(Matrix4 mat) const{
		return Matrix4(GLKMatrix4Add(_mat, mat._mat));
	}
	
	Matrix4 Matrix4::sub(Matrix4 mat) const{
		return Matrix4(GLKMatrix4Subtract(_mat, mat._mat));
	}
	
	Matrix4 Matrix4::mul(Matrix4 mat) const{
		return Matrix4(GLKMatrix4Multiply(_mat, mat._mat));
	}
	
	Vector3 Matrix4::mulVector3(Vector3 vec) const{
		GLKVector3 v = GLKVector3Make(vec.x(), vec.y(), vec.z());
		v = GLKMatrix4MultiplyVector3(_mat, v);
		return Vector3(v.x, v.y, v.z);
	}

}; // end namespace
