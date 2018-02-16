//  Created by ideawu on 18-2-10.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#include "Quaternion.h"
#include "util.h"

namespace a3d{

	Quaternion Quaternion::slerp(const Quaternion &q0, const Quaternion &q1, float progress){
		GLKQuaternion q = GLKQuaternionSlerp(q0._quat, q1._quat, progress);
		return Quaternion(q);
	}

	Quaternion::Quaternion(){
		_quat = GLKQuaternionIdentity;
	}

	Quaternion::Quaternion(float x, float y, float z, float w){
		_quat = GLKQuaternionMake(x, y, z, w);
	}

	Quaternion::Quaternion(float angle, const Vector3 &vec){
		_quat = GLKQuaternionMakeWithAngleAndAxis(degree_to_radian(angle), vec.x, vec.y, vec.z);
	}

	Quaternion::Quaternion(const GLKQuaternion &q){
		_quat = q;
	}

	float Quaternion::angle() const{
		return radian_to_degree(GLKQuaternionAngle(_quat));
	}

	Vector3 Quaternion::vector() const{
		GLKVector3 v = GLKQuaternionAxis(_quat);
		return Vector3(v.x, v.y, v.z);
	}

	float Quaternion::x() const{
		return _quat.x;
	}

	float Quaternion::y() const{
		return _quat.y;
	}

	float Quaternion::z() const{
		return _quat.z;
	}

	float Quaternion::w() const{
		return _quat.w;
	}

	Quaternion Quaternion::invert() const{
		return Quaternion(GLKQuaternionInvert(_quat));
		//return Quaternion(GLKQuaternionConjugate(_quat));
	}

	Quaternion Quaternion::add(const Quaternion &q) const{
		return Quaternion(GLKQuaternionAdd(_quat, q._quat));
	}

	Quaternion Quaternion::sub(const Quaternion &q) const{
		return Quaternion(GLKQuaternionSubtract(_quat, q._quat));
	}

	Quaternion Quaternion::mul(const Quaternion &q) const{
		return Quaternion(GLKQuaternionMultiply(_quat, q._quat));
	}

	Quaternion Quaternion::div(const Quaternion &q) const{
		return q.invert().mul(*this);
	}

}; // end namespace
