//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "AnimateOpacity.h"

namespace a3d{
	
	AnimateOpacity* AnimateOpacity::fadeTo(double opacity){
		AnimateOpacity *ret = new AnimateOpacity();
		ret->_opacity = opacity;
		return ret;
	}
	
	void AnimateOpacity::update(double progress, Node *target, const Node *origin){
		double df = progress * (_opacity - origin->opacity());
		target->opacity(origin->opacity() + df);
	}

}; // end namespace
