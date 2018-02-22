//  Created by ideawu on 18-2-11.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#include "AnimateScale.h"

namespace a3d{

	AnimateScale* AnimateScale::scale(const Vector3 &s){
		AnimateScale *ret = new AnimateScale();
		ret->_type = TypeOffset;
		ret->_scale = s;
		return ret;
	}

	AnimateScale* AnimateScale::scaleTo(const Vector3 &s){
		AnimateScale *ret = new AnimateScale();
		ret->_type = TypeTarget;
		ret->_scale = s;
		return ret;
	}

	void AnimateScale::update(double progress, Node *target){
		if(_type == TypeOffset){
			Vector3 s = Vector3::slerp(Vector3(1, 1, 1), _scale, progress);
			target->scale(s);
		}else if(_type == TypeTarget){
			Vector3 s = Vector3::slerp(target->scale(), _scale, progress);
			target->scaleTo(s);
		}
	}

}; // end namespace
