//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_AnimatePosition_hpp
#define a3d_AnimatePosition_hpp

#include "Animate.h"

namespace a3d{
	class AnimatePosition : public Animate
	{
	public:
		static AnimatePosition* move(const Vector3 &offset, double duration);
		static AnimatePosition* position(const Vector3 &pos, double duration);

		virtual void update(double progress, Node *target);
	private:
		typedef enum{
			TypeOffset,
			TypeTarget
		}AnimateType;
		
		AnimateType _type;
		Vector3 _vec;
	};
}; // end namespace

#endif /* AnimatePosition_hpp */
