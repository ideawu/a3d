//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "AnimatePosition.h"

namespace a3d{

	AnimatePosition* AnimatePosition::move(const Vector3 &vec){
		AnimatePosition *ret = new AnimatePosition();
		ret->_type = MoveTypeOffset;
		ret->_vec = vec;
		return ret;
	}
	
	AnimatePosition* AnimatePosition::moveTo(const Vector3 &pos){
		AnimatePosition *ret = new AnimatePosition();
		ret->_type = MoveTypePosition;
		ret->_vec = pos;
		return ret;
	}
	
	void AnimatePosition::update(float progress, Node *target, const Node *origin){
		Vector3 offset;
		if(_type == MoveTypeOffset){
			offset = _vec;
		}else{
			offset = _vec.sub(origin->position());
		}
		float len = progress * offset.length();
		offset = offset.normalize(len);
		Vector3 pos = origin->position().add(offset);
		target->position(pos);
	}

}; // end namespace
