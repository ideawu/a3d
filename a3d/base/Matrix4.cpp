//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Matrix4.h"

namespace a3d{

	Matrix4::Matrix4(){
		_mat = GLKMatrix4Identity;
	}

	Matrix4::Matrix4(const Quaternion &quat){
		GLKQuaternion q = GLKQuaternionMake(quat.x(), quat.y(), quat.z(), quat.w());
		if(fabs(q.x) + fabs(q.y) + fabs(q.z) + fabs(q.w) < 0.001){
			q = GLKQuaternionIdentity;
		}
		_mat = GLKMatrix4MakeWithQuaternion(q);
	}

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
		float x = this->mul(Vector3(1, 0, 0)).length();
		float y = this->mul(Vector3(0, 1, 0)).length();
		float z = this->mul(Vector3(0, 0, 1)).length();
		return Vector3(x, y, z);
	}

	void Matrix4::scaleTo(const Vector3 &scale){
		Vector3 st = this->scale();
		this->scale(scale.x * 1/st.x, scale.y * 1/st.y, scale.z * 1/st.z);
	}

//	static void quat_to_euler(const Quaternion &q, float *roll, float *pitch, float *yaw, const char *mode){
//		float r, p, y, w;
//		float sinr, cosr, sinp, siny, cosy;
//		float qs[3] = {q.x(), q.y(), q.z()};
//		w = q.w();
//		// 各轴顺序
//		int idx[3] = {mode[0]-'X', mode[1]-'X', mode[2]-'X'};
//		r = qs[idx[0]];
//		p = qs[idx[1]];
//		y = qs[idx[2]];
//		sinr = 2 * (w * r + p * y);
//		cosr = 1 - 2 * (r * r + p * p);
//		sinp = 2 * (w * p - r * y);
//		siny = 2 * (w * y + r * p);
//		cosy = 1 - 2 * (p * p + y * y);
//		sinr = trimf(sinr);
//		cosr = trimf(cosr);
//		sinp = trimf(sinp);
//		siny = trimf(siny);
//		cosy = trimf(cosy);
//
//		r = atan2(sinr, cosr);
//		if (fabs(sinp) >= 1){
//			p = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
//		}else{
//			p = asin(sinp);
//		}
//		y = atan2(siny, cosy);
//
//		*roll = r;
//		*pitch = p;
//		*yaw = y;
//	}
//
//	Vector3 Matrix4::rotation() const{
//		Vector3 r;
//		quat_to_euler(quaternion(), &r.x, &r.y, &r.z, "XYZ");
//		r.x = radian_to_degree(r.x);
//		r.y = radian_to_degree(r.y);
//		r.z = radian_to_degree(r.z);
//		return r;
//	}

	Quaternion Matrix4::quaternion() const{
//		Matrix4 mat = *this;
//		Vector3 s = mat.scale();
//		mat.scale(1/s.x, 1/s.y, 1/s.z);
//		GLKMatrix4 _mat = mat._mat;
//		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
//		float w = sqrt( fmax( 0, 1 + _mat.m00 + _mat.m11 + _mat.m22 ) ) / 2;
//		float x = sqrt( fmax( 0, 1 + _mat.m00 - _mat.m11 - _mat.m22 ) ) / 2;
//		float y = sqrt( fmax( 0, 1 - _mat.m00 + _mat.m11 - _mat.m22 ) ) / 2;
//		float z = sqrt( fmax( 0, 1 - _mat.m00 - _mat.m11 + _mat.m22 ) ) / 2;
//		x = copysignf(x, _mat.m21 - _mat.m12);
//		y = copysignf(y, _mat.m02 - _mat.m20);
//		z = copysignf(z, _mat.m10 - _mat.m01);
//		return Quaternion(x, y, z, w);

		Matrix4 mat = *this;
		mat.resetScale();
		// 注意！GLKQuaternionMakeWithMatrix4 的参数不能包含缩放！FUCK！
		GLKQuaternion q = GLKQuaternionMakeWithMatrix4(mat._mat);
		return Quaternion(q.x, q.y, q.z, q.w);
	}

	void Matrix4::quaternion(const Quaternion &quat){
		Quaternion q = this->quaternion();
		this->rotate(-q.angle(), q.vector());
		this->rotate(quat.angle(), quat.vector());
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
		if(vec.empty()){
			return;
		}
		_mat = GLKMatrix4Rotate(_mat, degree_to_radian(degree), vec.x, vec.y, vec.z);
	}
	
	void Matrix4::rotate(float degree, const Axis &axis){
		if(axis.direction.empty()){
			return;
		}
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

	void Matrix4::resetScale(){
		Vector3 s = this->scale();
		this->scale(1/s.x, 1/s.y, 1/s.z);
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
//		return this->invert().mul(mat);
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
