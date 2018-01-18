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
		ret.matrix = second.div(first);
		
		return ret;
	}
}; // end namespace

