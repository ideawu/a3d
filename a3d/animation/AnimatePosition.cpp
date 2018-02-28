//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "AnimatePosition.h"

namespace a3d{

	AnimatePosition* AnimatePosition::move(const Vector3 &offset, double duration){
		AnimatePosition *ret = new AnimatePosition();
		ret->duration(duration);
		ret->_type = TypeOffset;
		ret->_vec = offset;
		return ret;
	}
	
	AnimatePosition* AnimatePosition::position(const Vector3 &pos, double duration){
		AnimatePosition *ret = new AnimatePosition();
		ret->duration(duration);
		ret->_type = TypeTarget;
		ret->_vec = pos;
		return ret;
	}
	
	void AnimatePosition::update(double progress, Node *target){
		if(_type == TypeOffset){
			Vector3 offset = Vector3::slerp(Vector3(), _vec, progress);
			target->move(offset);
		}else if(_type == TypeTarget){
			Vector3 pos = Vector3::slerp(target->position(), _vec, progress);
			target->position(pos);
		}
	}

}; // end namespace
