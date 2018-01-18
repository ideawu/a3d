//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include "Matrix4.h"
#include "Vector3.h"

namespace a3d{
	class Transform
	{
	public:
		Vector3 size;
		Matrix4 matrix;
	};
}; // end namespace

#endif /* Transform_hpp */
