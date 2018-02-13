//  Created by ideawu on 02/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "AnimateRotation.h"

namespace a3d{

	AnimateRotation* AnimateRotation::rotate(float degree, const Vector3 &vec){
		AnimateRotation *ret = new AnimateRotation();
		ret->_type = TypeVector;
		ret->_degree = degree;
		ret->_vec = vec;
		return ret;
	}
	
	AnimateRotation* AnimateRotation::rotate(float degree, const Axis &axis){
		AnimateRotation *ret = new AnimateRotation();
		ret->_type = TypeAxis;
		ret->_degree = degree;
		ret->_axis = axis;
		return ret;
	}

	AnimateRotation* AnimateRotation::rotateTo(const Quaternion &quat){
		AnimateRotation *ret = new AnimateRotation();
		ret->_type = TypeQuaternion;
		ret->_quat = quat;
		return ret;
	}

	void AnimateRotation::update(double progress, Node *target){
		float angle = _degree * progress;
		if(_type == TypeVector){
			target->rotate(angle, _vec);
		}else if(_type == TypeAxis){
//			log_debug("%f", angle);
			target->rotate(angle, _axis);
		}else if(_type == TypeQuaternion){
			// 避免计算误差
			if(progress == 1){
				target->quaternion(_quat);
			}else{
				Quaternion q0 = target->matrix().quaternion();
				Quaternion q = Quaternion::slerp(q0, _quat, progress);
				target->quaternion(q);
//				log_debug("%f %s", q0.angle(), q0.vector().str().c_str());
//				log_debug("%f", progress);
//				log_debug("%f %s", q.angle(), q.vector().str().c_str());
//				log_debug("%f %s", target->quaternion().angle(), target->quaternion().vector().str().c_str());
			}
		}
//		log_debug("%f", target->quaternion().angle());
	}
	
}; // end namespace
