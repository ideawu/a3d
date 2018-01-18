//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "AnimatePosition.h"
#include "Node.h"

namespace a3d{

	AnimatePosition AnimatePosition::move(Vector3 offset){
		AnimatePosition ret;
		ret._type = MoveTypeOffset;
		ret._vec = offset;
		return ret;
	}
	
	AnimatePosition AnimatePosition::moveTo(Vector3 pos){
		AnimatePosition ret;
		ret._type = MoveTypeDestination;
		ret._vec = pos;
		return ret;
	}
	
	void AnimatePosition::update(float progress, Node *current, const Node *origin){
		Vector3 offset;
		if(_type == MoveTypeOffset){
			offset = _vec;
		}else{
			offset = _vec.sub(origin->pos());
		}
		
		float len = progress * offset.length();
		offset = offset.normalize(len);
		current->move(offset);
	}

}; // end namespace
