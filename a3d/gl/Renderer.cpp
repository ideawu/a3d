//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Renderer.h"
#include "Context.h"

namespace a3d{

	Renderer::Renderer(){
		_opacity = 1;
		_stencilRef = 0;
	}
	
	Renderer* Renderer::current(){
		return Context::current()->renderer();
	}

	float Renderer::opacity() const{
		return _opacity;
	}

	void Renderer::pushOpacity(float opacity){
		_opacity_list.push_back(_opacity);
		_opacity *= opacity;
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glColor4f(_color.r, _color.g, _color.b, _color.a);
		// premultiplied alpha
		// glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		//glColor4f(_color.r*_color.a, _color.g*_color.a, _color.b*_color.a, _color.a);
		glColor4f(_opacity, _opacity, _opacity, _opacity);
	}
	
	void Renderer::popOpacity(){
		_opacity = _opacity_list.back();
		_opacity_list.pop_back();
		glColor4f(_opacity, _opacity, _opacity, _opacity);
	}

	void Renderer::pushMatrix(const Matrix4 &mat){
		glPushMatrix();
		glMultMatrixf((const GLfloat *)mat.array());
	}
	
	void Renderer::popMatrix(){
		glPopMatrix();
	}
	
	void Renderer::pushStencil(){
		if(_stencilRef == 0){
			glEnable(GL_STENCIL_TEST);
			glClearStencil(0);
			glClear(GL_STENCIL_BUFFER_BIT);
		}
		glStencilFunc(GL_EQUAL, _stencilRef, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
		_stencilRef ++;
	}
	
	void Renderer::popStencil(){
		// TODO: clear stencil buffer with value=_stencilRef
		_stencilRef --;
		if(_stencilRef == 0){
			glDisable(GL_STENCIL_TEST);
		}else{
			glStencilFunc(GL_EQUAL, _stencilRef, 0xff);
			glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
		}
	}

}; // end namespace

