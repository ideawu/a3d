//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Transform_hpp
#define a3d_Transform_hpp

#include "Matrix4.h"
#include "Vector3.h"

namespace a3d{
	class Object;
	
	class Transform
	{
	public:
		static Transform transformBetween(const Object &first, const Object &second);
		
		Matrix4 matrix;
		Vector3 size;
		// TODO: opacity
	};
}; // end namespace

#endif /* Transform_hpp */
