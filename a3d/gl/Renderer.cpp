//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Renderer.h"

namespace a3d{

	Renderer::Renderer(){
		pushOpacity(1.0);
	}
	
	void Renderer::pushOpacity(float opacity){
		_q_opacity.push_back(_color.a);
		_color.a *= opacity;
		glColor4f(_color.r, _color.g, _color.b, _color.a);
	}
	
	void Renderer::popOpacity(){
		float opacity = _q_opacity.back();
		_q_opacity.pop_back();
		_color.a = opacity;
		glColor4f(_color.r, _color.g, _color.b, _color.a);
	}

}; // end namespace

