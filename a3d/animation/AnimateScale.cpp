//  Created by ideawu on 18-2-11.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#include "AnimateScale.h"

namespace a3d{

	AnimateScale* AnimateScale::scale(const Vector3 &s){
		AnimateScale *ret = new AnimateScale();
		ret->_scale = s;
		return ret;
	}

	void AnimateScale::update(double progress, Node *target, const Node *origin){
		// 将 target 的 scale 恢复为 origin
		target->scaleTo(origin->scale());

		// 避免计算误差
		if(progress == 1){
			target->scale(_scale);
//			log_debug("%f", target->scale().x);
		}else{
			Vector3 s = Vector3::slerp(Vector3(1, 1, 1), _scale, progress);
			target->scale(s);
//			log_debug("%f", target->scale().x);
		}
	}

}; // end namespace
