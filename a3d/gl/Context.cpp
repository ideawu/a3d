//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Context.h"
#include "SharedContext.h"
#include "BufferContext.h"

namespace a3d{
	static Context *_current = NULL;
	static Context *_shared = NULL;

	Context* Context::current(){
		if(!_current){
			_current = Context::shared();
		}
		return _current;
	}

	Context* Context::shared(){
		if(!_shared){
			_shared = new SharedContext();
			_shared->setup();
		}
		return _shared;
	}

	Context* Context::bufferContext(float width, float height){
		BufferContext *impl = new BufferContext();
		impl->width(width);
		impl->height(height);
		impl->setup();
		return impl;
	}
	
	Context::Context(){
		_width = 0;
		_height = 0;
		_renderer = new Renderer();
	}

	Context::~Context(){
		delete _renderer;
	}

	void Context::makeCurrent(){
		_current = this;
		if(_width > 0 && _height > 0){
			glViewport(0, 0, _width, _height);
		}
		if(framebuffer()){
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer());
		}
	}

	Renderer* Context::renderer() const{
		return _renderer;
	}

	float Context::width() const{
		return _width;
	}
	
	float Context::height() const{
		return _height;
	}
	
	void Context::width(float width){
		_width = (int)((double)width/2 + 0.5) * 2;
	}
	
	void Context::height(float height){
		_height = (int)((double)height/2 + 0.5) * 2;
	}

	void Context::loadMatrix3D(const Matrix4 &mat){
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat *)mat.array());
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void Context::loadMatrix2D(const Matrix4 &mat){
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat *)mat.array());
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glDisable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void Context::clear(){
		clear(0, 0, 0, 1);
	}
	
	void Context::clear(float r, float g, float b, float a){
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	
	void Context::flush(){
		glFlush();
	}

	void Context::finish(){
		glFinish();
	}
	
	void Context::blit(){
		if(framebuffer()){
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer());
			glBlitFramebuffer(0, 0, (GLsizei)_width, (GLsizei)_height,
							  0, 0, (GLsizei)_width, (GLsizei)_height,
							  GL_COLOR_BUFFER_BIT, GL_NEAREST); // GL_LINEAR GL_NEAREST
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		glFinish();
	}

}; // end namespace
