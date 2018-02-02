//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef AnimateOpacity_hpp
#define AnimateOpacity_hpp

#include "Animate.h"

namespace a3d{
	class AnimateOpacity : public Animate
	{
	public:
		static AnimateOpacity* fadeTo(double opacity);
		
		virtual void update(double progress, Node *target, const Node *origin);
	private:
		float _opacity;
	};
}; // end namespace

#endif /* AnimateOpacity_hpp */
