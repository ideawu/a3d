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

	void AnimateSize::update(double progress, Node *target, const Node *origin){
		// 避免计算误差
		if(progress == 1){
			target->size(_size);
		}else{
			Vector3 size = Vector3::slerp(origin->size(), _size, progress);
			target->size(size);
		}
	}

}; // end namespace
