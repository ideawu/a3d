//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Axis_hpp
#define Axis_hpp

#include "Point3.h"
#include "Vector3.h"

namespace a3d{
	class Axis
	{
	public:
		Axis();
		Axis(const Point3 &origin, const Point3 &target);
		Axis(const Point3 &origin, const Vector3 &direction);

	public:
		Point3 origin;
		Vector3 direction;
		
		Point3 nearestPointTo(const Point3 &target) const;
	};
	
}; // end namespace

#endif /* Axis_hpp */
