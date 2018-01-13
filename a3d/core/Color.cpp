//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Color.h"

namespace a3d{
	Color::Color(){
		r = g = b = a = 1;
	}

	Color::Color(float r, float g, float b, float a){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
}; // end namespace
