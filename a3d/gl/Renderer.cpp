//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Renderer.h"
#include "Context.h"

namespace a3d{

	Renderer::Renderer(){
		_opacity = 1;
	}
	
	Renderer* Renderer::current(){
		return Context::current()->renderer();
	}

	float Renderer::opacity() const{
		return _opacity;
	}

	void Renderer::pushOpacity(float opacity){
		_q_opacity.push_back(_opacity);
		_opacity *= opacity;
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glColor4f(_color.r, _color.g, _color.b, _color.a);
		// premultiplied alpha
		// glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		//glColor4f(_color.r*_color.a, _color.g*_color.a, _color.b*_color.a, _color.a);
		glColor4f(_opacity, _opacity, _opacity, _opacity);
	}
	
	void Renderer::popOpacity(){
		_opacity = _q_opacity.back();
		_q_opacity.pop_back();
		glColor4f(_opacity, _opacity, _opacity, _opacity);
	}

	void Renderer::pushMatrix(const Matrix4 &mat){
		glPushMatrix();
		glMultMatrixf((const GLfloat *)mat.array());
	}
	
	void Renderer::popMatrix(){
		glPopMatrix();
	}

}; // end namespace

