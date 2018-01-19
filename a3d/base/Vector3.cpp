//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Vector3.h"

namespace a3d{
	
	Vector3::Vector3(){
		_x = 0;
		_y = 0;
		_z = 0;
	}

	Vector3::Vector3(float x, float y, float z){
		_x = x;
		_y = y;
		_z = z;
	}

	float Vector3::x() const{
		return _x;
	}
	
	void Vector3::x(float x){
		_x = x;
	}

	float Vector3::y() const{
		return _y;
	}
	
	void Vector3::y(float y){
		_y = y;
	}

	float Vector3::z() const{
		return _z;
	}
	
	void Vector3::z(float z){
		_z = z;
	}

	float Vector3::length() const{
		return sqrt(_x*_x + _y*_y + _z*_z);
	}
	
	Vector3 Vector3::normalize() const{
		return normalize(1);
	}
	
	Vector3 Vector3::normalize(float norm) const{
		// TODO: Fast inverse square root?
		float len = this->length();
		if(len == 0){
			return *this;
		}
		return this->mul(norm/len);
	}
	
	Vector3 Vector3::negate() const{
		return Vector3(-_x, -_y, -_z);
	}
	
	// alias of negate
	Vector3 Vector3::invert() const{
		return this->negate();
	}
	
	Vector3 Vector3::add(const Vector3 &vec) const{
		return Vector3(_x + vec._x, _y + vec._y, _z + vec._z);
	}
	
	Vector3 Vector3::sub(const Vector3 &vec) const{
		return Vector3(_x - vec._x, _y - vec._y, _z - vec._z);
	}

	Vector3 Vector3::mul(float scalar) const{
		return Vector3(_x * scalar, _y * scalar, _z * scalar);
	}

	float Vector3::dot(const Vector3 &vec) const{
		return (_x * vec._x) + (_y * vec._y) + (_z * vec._z);
	}
	
	Vector3 Vector3::cross(const Vector3 &vec) const{
		float x = _y * vec._z - _z * vec._y;
		float y = _z * vec._x - _x * vec._z;
		float z = _x * vec._y - _y * vec._x;
		return Vector3(x, y, z);
	}
	
	Vector3 Vector3::project(const Vector3 &vec) const{
		float a = this->dot(vec);
		float b = vec.dot(vec);
		return vec.mul(a/b);
	}

}; // end namespace
