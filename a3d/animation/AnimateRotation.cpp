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

	void AnimateRotation::update(double progress, Node *target, const Node *origin){
		float angle = _degree * progress;
		if(_type == TypeVector){
			target->rotate(angle, _vec);
		}else{
			target->rotate(angle, _axis);
		}
	}
}; // end namespace
