//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "AnimateOpacity.h"

namespace a3d{
	
	AnimateOpacity* AnimateOpacity::fadeTo(double opacity, double duration){
		AnimateOpacity *ret = new AnimateOpacity();
		ret->duration(duration);
		ret->_opacity = opacity;
		return ret;
	}
	
	void AnimateOpacity::update(double progress, Node *target, const Node *origin){
		// 避免计算误差
		if(progress == 1){
			target->opacity(_opacity);
		}else{
			double df = progress * (_opacity - origin->opacity());
			target->opacity(origin->opacity() + df);
		}
	}

}; // end namespace
