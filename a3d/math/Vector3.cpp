//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Vector3.h"

namespace a3d{
	
	Vector3::Vector3(){
		_vec.x = 0;
		_vec.y = 0;
		_vec.z = 0;
	}

	Vector3::Vector3(const Vector3 &vec){
		_vec = vec._vec;
	}

	Vector3::Vector3(float x, float y, float z){
		_vec.x = x;
		_vec.y = y;
		_vec.z = z;
	}

	Vector3::Vector3(GLKVector3 vec){
		_vec = vec;
	}

	Vector3 Vector3::zero(){
		return Vector3(0, 0, 0);
	}

	float Vector3::x() const{
		return _vec.x;
	}
	
	void Vector3::x(float x){
		_vec.x = x;
	}

	float Vector3::y() const{
		return _vec.y;
	}
	
	void Vector3::y(float y){
		_vec.y = y;
	}

	float Vector3::z() const{
		return _vec.z;
	}
	
	void Vector3::z(float z){
		_vec.z = z;
	}

	float Vector3::length() const{
		return GLKVector3Length(_vec);
	}
	
	Vector3 Vector3::normalize() const{
		return Vector3(GLKVector3Normalize(_vec));
	}
	
	Vector3 Vector3::normalize(float norm) const{
		float len = this->length();
		return Vector3(GLKVector3MultiplyScalar(_vec, norm/len));
	}
	
	Vector3 Vector3::negate() const{
		return Vector3(GLKVector3Negate(_vec));
	}
	
	// alias of negate
	Vector3 Vector3::invert() const{
		return this->negate();
	}
	
	Vector3 Vector3::add(Vector3 vec) const{
		return Vector3(GLKVector3Add(_vec, vec._vec));
	}
	
	Vector3 Vector3::sub(Vector3 vec) const{
		return Vector3(GLKVector3Subtract(_vec, vec._vec));
	}
	
	float Vector3::dot(Vector3 vec) const{
		return GLKVector3DotProduct(_vec, vec._vec);
	}
	
	Vector3 Vector3::cross(Vector3 vec) const{
		return Vector3(GLKVector3CrossProduct(_vec, vec._vec));
	}
	
	Vector3 Vector3::project(Vector3 vec) const{
		return Vector3(GLKVector3Project(_vec, vec._vec));
	}

}; // end namespace
