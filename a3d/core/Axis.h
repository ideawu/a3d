//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Axis_hpp
#define Axis_hpp

#include "Vector3.h"

namespace a3d{
	class Axis
	{
	private:
		Axis(const Axis &axis){}
		
	public:
		Axis(const Vector3 &origin, const Vector3 &direction);
		
	public:
		Vector3 origin;
		Vector3 direction;
		
		Vector3 nearestPointTo(const Vector3 &target) const;
	};
	
}; // end namespace

#endif /* Axis_hpp */
