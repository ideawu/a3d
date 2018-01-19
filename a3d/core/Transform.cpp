//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Transform.h"
#include "Object.h"

namespace a3d{

	Transform Transform::transformBetween(const Object &first, const Object &second){
		Transform ret;
		
		// size 变动
		Vector3 size1 = first.size();
		Vector3 size2 = second.size();
		ret.size = size2.sub(size1);
		
		// matrix 变动
		Matrix4 mat1 = first.matrix();
		Matrix4 mat2 = second.matrix();
		ret.matrix = mat2.div(mat1);
		
		return ret;
	}
}; // end namespace

