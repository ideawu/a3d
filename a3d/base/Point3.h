//  Created by ideawu on 25/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Point3_hpp
#define Point3_hpp

#include "Vector3.h"

namespace a3d{
	
	// 向量和点跟矩阵的运算方式不一样，所以是两个不同的类型
	class Point3 : public Vector3
	{
	public:
		Point3(){}
		Point3(float x, float y, float z);
		Point3(const Vector3 &vec);
	};

}; // end namespace

#endif /* Point3_hpp */
