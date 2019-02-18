//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Renderer.h"

namespace a3d{

	Renderer::Renderer(){
		_opacity = 1;
		_stencilRef = 0;
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
		if(_opacity < 1){
			glDisable(GL_DEPTH_TEST);
		}
	}
	
	void Renderer::popOpacity(){
		_opacity = _opacity_list.back();
		_opacity_list.pop_back();
		glColor4f(_opacity, _opacity, _opacity, _opacity);
		if(_opacity >= 1){
			glEnable(GL_DEPTH_TEST);
		}
	}

	void Renderer::pushMatrix(const Matrix4 &mat){
		glPushMatrix();
		glMultMatrixf((const GLfloat *)mat.array());
	}
	
	void Renderer::popMatrix(){
		glPopMatrix();
	}

	void Renderer::clearStencil(){
		glEnable(GL_STENCIL_TEST);
		glStencilMask(0xff);
		glClearStencil(0);
		glClear(GL_STENCIL_BUFFER_BIT);
		_stencilRef = 0;
	}

	void Renderer::pushStencil(){
		if(_stencilRef == 0){
			clearStencil();
		}
		glStencilFunc(GL_EQUAL, _stencilRef, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
		_stencilRef ++;
	}

	void Renderer::bindStencil(){
		glStencilFunc(GL_EQUAL, _stencilRef, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	}

	static void _decrStencil(int ref);

	void Renderer::popStencil(){
		beginStencil();
		_decrStencil(_stencilRef);
		endStencil();

		_stencilRef --;
		if(_stencilRef == 0){
			glDisable(GL_STENCIL_TEST);
		}else{
			glStencilFunc(GL_EQUAL, _stencilRef, 0xff);
			glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
		}
	}

	void Renderer::beginStencil(){
		glDisable(GL_DEPTH_TEST);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	}
	
	void Renderer::endStencil(){
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glEnable(GL_DEPTH_TEST);
	}

	static void _decrStencil(int ref){
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		
		glStencilFunc(GL_EQUAL, ref, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
		{
			glColor3f(1, 1, 1);
			glBegin(GL_POLYGON);
			{
				glVertex2i(-1, -1);
				glVertex2i(1, -1);
				glVertex2i(1, 1);
				glVertex2i(-1, 1);
			}
			glEnd();
			glBegin(GL_POLYGON);
			{
				glVertex2i(-1, -1);
				glVertex2i(-1, 1);
				glVertex2i(1, 1);
				glVertex2i(1, -1);
			}
			glEnd();
		}
		
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

}; // end namespace

