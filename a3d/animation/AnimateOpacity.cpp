//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "AnimateOpacity.h"

namespace a3d{
	
	AnimateOpacity* AnimateOpacity::opacity(double opacity, double duration){
		AnimateOpacity *ret = new AnimateOpacity();
		ret->duration(duration);
		ret->_opacity = opacity;
		return ret;
	}
	
	void AnimateOpacity::update(double progress, Node *target){
		// 避免计算误差
		if(progress == 1){
			target->opacity(_opacity);
		}else{
			float opacity = progress * (_opacity - target->opacity()) + target->opacity();
			target->opacity(opacity);
		}
	}

}; // end namespace
