//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include "Node.h"

namespace a3d{
	class Animate
	{
	public:
		Animate();
		Animate(const Animate &a);
		~Animate();
		void updateAtTime(float time);
	private:
		Node *_target;
		float _beginTime;
		float _duration;
	};
}; // end namespace

#endif /* Animation_hpp */
