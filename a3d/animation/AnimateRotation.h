//  Created by ideawu on 02/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_AnimateRotation_hpp
#define a3d_AnimateRotation_hpp

#include "Animate.h"

namespace a3d{
	class AnimateRotation : public Animate
	{
	public:
		static AnimateRotation* rotate(float degree, const Vector3 &vec);
		static AnimateRotation* rotate(float degree, const Axis &axis);
		static AnimateRotation* rotateTo(const Quaternion &quat);

		virtual void update(double progress, Node *target);
	private:
		typedef enum{
			TypeVector,
			TypeAxis,
			TypeQuaternion,
		}AnimateType;
		
		AnimateType _type;
		float _degree;
		Vector3 _vec;
		Axis _axis;
		Quaternion _quat;
	};
}; // end namespace

#endif /* AnimateRotation_hpp */
