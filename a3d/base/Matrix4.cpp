//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Matrix4.h"

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

	std::string Matrix4::str() const{
		std::string s;
		char buf[32];
		const float *m = this->array();
		for(int i=0; i<16; i++){
			snprintf(buf, sizeof(buf), "%8.2f", m[i]);
			s.append(buf);
			if(i % 4 == 3){
				s.push_back('\n');
			}else{
				s.push_back(' ');
			}
		}
		return s;
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

	Vector3 Matrix4::position() const{
		return Vector3(x(), y(), z());
	}
	
	void Matrix4::position(const Vector3 &pos){
		this->x(pos.x);
		this->y(pos.y);
		this->z(pos.z);
	}
	
	void Matrix4::position(float x, float y, float z){
		this->x(x);
		this->y(y);
		this->z(z);
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
	
	Vector3 Matrix4::scale() const{
		Vector3 vec = Vector3(1, 1, 1);
		vec = this->mul(vec);
		return vec;
	}
	
	void Matrix4::translate(float x, float y, float z){
		// macOS < 10.13, GLKMatrix4Translate does not work correctly!
		//_mat = GLKMatrix4Translate(_mat, x, y, z);
		_mat = {
			_mat.m[0], _mat.m[1], _mat.m[2],  _mat.m[3],
			_mat.m[4], _mat.m[5], _mat.m[6],  _mat.m[7],
			_mat.m[8], _mat.m[9], _mat.m[10], _mat.m[11],
			_mat.m[0] * x + _mat.m[4] * y + _mat.m[8]  * z + _mat.m[12],
			_mat.m[1] * x + _mat.m[5] * y + _mat.m[9]  * z + _mat.m[13],
			_mat.m[2] * x + _mat.m[6] * y + _mat.m[10] * z + _mat.m[14],
			_mat.m[3] * x + _mat.m[7] * y + _mat.m[11] * z + _mat.m[15]
		};
	}
	
	void Matrix4::translate(const Vector3 &offset){
		this->translate(offset.x, offset.y, offset.z);
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
		_mat = GLKMatrix4Rotate(_mat, degree_to_radian(degree), vec.x, vec.y, vec.z);
	}
	
	void Matrix4::rotate(float degree, const Axis &axis){
		this->translate(axis.origin);
		this->Matrix4::rotate(degree, axis.direction);
		this->translate(axis.origin.invert());
	}

	void Matrix4::scale(float xyz){
		this->scale(xyz, xyz, xyz);
	}

	void Matrix4::scale(const Vector3 &scale){
		this->scale(scale.x, scale.y, scale.z);
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

	Vector3 Matrix4::mul(const Vector3 &vec) const{
		GLKVector3 v = GLKVector3Make(vec.x, vec.y, vec.z);
		v = GLKMatrix4MultiplyVector3(_mat, v);
		return Vector3(v.x, v.y, v.z);
	}
	
	Point3 Matrix4::mul(const Point3 &pos) const{
		GLKVector3 v = GLKVector3Make(pos.x, pos.y, pos.z);
		v = GLKMatrix4MultiplyVector3WithTranslation(_mat, v);
		return Point3(v.x, v.y, v.z);
	}

}; // end namespace
