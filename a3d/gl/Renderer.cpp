//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Renderer.h"
#include "Context.h"

namespace a3d{

	Renderer::Renderer(){
	}
	
	Renderer* Renderer::current(){
		return Context::current()->renderer();
	}

	float Renderer::opacity() const{
		return _color.a;
	}

	void Renderer::pushOpacity(float opacity){
		_q_opacity.push_back(_color.a);
		_color.a *= opacity;
		glColor4f(_color.r, _color.g, _color.b, _color.a);
	}
	
	void Renderer::popOpacity(){
		_color.a = _q_opacity.back();
		_q_opacity.pop_back();
		glColor4f(_color.r, _color.g, _color.b, _color.a);
	}

	void Renderer::pushMatrix(const Matrix4 &mat){
		glPushMatrix();
		glMultMatrixf((const GLfloat *)mat.array());
	}
	
	void Renderer::popMatrix(){
		glPopMatrix();
	}

	
	
	GLuint Renderer::createTexture(const char *pixels, int width, int height){
		GLuint tid;
		glGenTextures(1, &tid);
		//		log_debug("gen tid %d", tid);
		glBindTexture(GL_TEXTURE_2D, tid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // LINEAR 使用平均算法，抗锯齿
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
		return tid;
	}

}; // end namespace

