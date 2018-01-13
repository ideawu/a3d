//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Object.h"

namespace a3d{
	Object::Object(){
		_width = 0;
		_height = 0;
		_depth = 0;
	}
	
	float Object::width() const{
		return _width;
	}
	
	float Object::height() const{
		return _height;
	}
	
	float Object::depth() const{
		return _depth;
	}
	
	void Object::width(float w){
		_width = w;
	}
	
	void Object::height(float h){
		_height = h;
	}
	
	void Object::depth(float d){
		_depth = d;
	}
	
	void Object::move(float x, float y, float z){
		this->translate(x, y, z);
	}
	
}; // end namespace
