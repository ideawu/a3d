//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "AnimatePosition.h"

namespace a3d{

	AnimatePosition* AnimatePosition::move(const Vector3 &vec){
		AnimatePosition *ret = new AnimatePosition();
		ret->_type = TypeOffset;
		ret->_vec = vec;
		return ret;
	}
	
	AnimatePosition* AnimatePosition::moveTo(const Vector3 &pos){
		AnimatePosition *ret = new AnimatePosition();
		ret->_type = TypePosition;
		ret->_vec = pos;
		return ret;
	}
	
	void AnimatePosition::update(double progress, Node *target, const Node *origin){
		Vector3 offset;
		if(_type == TypeOffset){
			offset = Vector3::slerp(Vector3(), _vec, progress);
		}else{
			offset = Vector3::slerp(origin->position(), _vec, progress);
		}
		target->move(offset);
	}

}; // end namespace
