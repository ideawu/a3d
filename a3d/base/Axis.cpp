//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Axis.h"

namespace a3d{
	Axis::Axis(){
	}
	
	Axis::Axis(const Vector3 &origin, const Vector3 &direction){
		this->origin = origin;
		this->direction = direction.normalize();
	}
	
	Vector3 Axis::nearestPointTo(const Vector3 &target) const{
		Vector3 vec = target.sub(this->origin);
		float dot = vec.dot(this->direction);
		if(dot < 0){
			return this->origin;
		}else{
			return this->origin.add(this->direction.normalize(dot));
		}
	}

}; // end namespace

