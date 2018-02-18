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
		// 返回 first 要到达 second，需要在父坐标系内做的变换
		static Transform transformBetween(const Object &first, const Object &second);
		
		float opacity;
		Vector3 size;
		// 注意：这里的变换，是指在父坐标系内的变换，而不是在 first 坐标系内的变换
		Matrix4 matrix;
	};
}; // end namespace

#endif /* Transform_hpp */
