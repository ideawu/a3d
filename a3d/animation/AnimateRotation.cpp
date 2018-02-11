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

	void AnimateRotation::update(double progress, Node *target, const Node *origin){
		float angle = _degree * progress;
		if(_type == TypeVector){
			target->rotate(angle, _vec);
		}else if(_type == TypeAxis){
//			log_debug("%f", angle);
			target->rotate(angle, _axis);
		}else if(_type == TypeQuaternion){
			// 避免计算误差
			if(progress == 1){
				target->rotateTo(_quat);
			}else{
				Quaternion q0 = origin->matrix().quaternion();
				Quaternion q = Quaternion::slerp(q0, _quat, progress);
				target->rotateTo(q);
			}
		}
	}
}; // end namespace
