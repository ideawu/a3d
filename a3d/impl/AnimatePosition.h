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
		static AnimatePosition* move(const Vector3 &vec);
		static AnimatePosition* moveTo(const Vector3 &pos);

		virtual void update(double progress, Node *target, const Node *origin);
	private:
		typedef enum{
			TypeOffset,
			TypePosition
		}AnimateType;
		
		AnimateType _type;
		Vector3 _vec;
	};
}; // end namespace

#endif /* AnimatePosition_hpp */
