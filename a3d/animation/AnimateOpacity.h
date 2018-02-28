//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_AnimateOpacity_hpp
#define a3d_AnimateOpacity_hpp

#include "Animate.h"

namespace a3d{
	class AnimateOpacity : public Animate
	{
	public:
		static AnimateOpacity* opacity(double opacity, double duration);
		
		virtual void update(double progress, Node *target);
	private:
		float _opacity;
	};
}; // end namespace

#endif /* AnimateOpacity_hpp */
