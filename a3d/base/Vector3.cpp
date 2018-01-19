//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Vector3.h"

namespace a3d{
	
	Vector3::Vector3(){
		x = y = z = 0;
	}

	Vector3::Vector3(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float Vector3::length() const{
		return sqrt(x*x + y*y + z*z);
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
		return Vector3(-x, -y, -z);
	}
	
	// alias of negate
	Vector3 Vector3::invert() const{
		return this->negate();
	}
	
	Vector3 Vector3::add(const Vector3 &vec) const{
		return Vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	}
	
	Vector3 Vector3::sub(const Vector3 &vec) const{
		return Vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	Vector3 Vector3::mul(float scalar) const{
		return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
	}

	float Vector3::dot(const Vector3 &vec) const{
		return (this->x * vec.x) + (this->y * vec.y) + (this->z * vec.z);
	}
	
	Vector3 Vector3::cross(const Vector3 &vec) const{
		float x = this->y * vec.z - this->z * vec.y;
		float y = this->z * vec.x - this->x * vec.z;
		float z = this->x * vec.y - this->y * vec.x;
		return Vector3(x, y, z);
	}
	
	Vector3 Vector3::project(const Vector3 &vec) const{
		float a = this->dot(vec);
		float b = vec.dot(vec);
		return vec.mul(a/b);
	}

}; // end namespace
