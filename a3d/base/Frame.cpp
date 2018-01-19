//  Created by ideawu on 19/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Frame.h"

namespace a3d{
	
	Frame::Frame(){
		x = y = width = height = 0;
	}
	
	Frame::Frame(float x, float y, float width, float height){
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
}; // end namespace
