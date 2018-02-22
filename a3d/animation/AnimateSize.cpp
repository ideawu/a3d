//  Created by ideawu on 18-2-11.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#include "AnimateSize.h"

namespace a3d{

	AnimateSize* AnimateSize::size(const Vector3 &size){
		AnimateSize *ret = new AnimateSize();
		ret->_size = size;
		return ret;
	}

	void AnimateSize::update(double progress, Node *target){
		Vector3 size = Vector3::slerp(target->size(), _size, progress);
		target->size(size);
	}

}; // end namespace
