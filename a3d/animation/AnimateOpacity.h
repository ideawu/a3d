//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef AnimateOpacity_hpp
#define AnimateOpacity_hpp

#include "Animate.h"
#include "Node.h"

namespace a3d{
	class AnimateOpacity : public Animate
	{
	public:
		static AnimateOpacity* fadeTo(float opacity);
		
		virtual void update(float progress, Node *current, const Node *origin);
	private:
		float _opacity;
	};
}; // end namespace

#endif /* AnimateOpacity_hpp */
