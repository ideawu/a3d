//  Created by ideawu on 02/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef AnimateRotation_hpp
#define AnimateRotation_hpp

#include "Animate.h"

namespace a3d{
	class AnimateRotation : public Animate
	{
	public:
		static AnimateRotation* rotate(float degree, const Vector3 &vec);
		static AnimateRotation* rotate(float degree, const Axis &axis);
		
		virtual void update(double progress, Node *target, const Node *origin);

	private:
		typedef enum{
			TypeVector,
			TypeAxis
		}AnimateType;
		
		AnimateType _type;
		float _degree;
		Vector3 _vec;
		Axis _axis;
	};
}; // end namespace

#endif /* AnimateRotation_hpp */
