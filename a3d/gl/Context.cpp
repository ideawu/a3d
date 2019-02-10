//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Context.h"
#include "BlankContext.h"
#include "BufferContext.h"
#include "Renderer.h"

namespace a3d{
	static Context *_current = NULL;
	static Context *_shared = NULL;

	Context* Context::current(){
		if(!_current){
			_shared = Context::blankContext();
			_current = _shared;
		}
		return _current;
	}

	Context* Context::blankContext(){
		return new BlankContext();
	}

	Context* Context::bufferContext(int width, int height, int samples){
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

	Renderer* Context::renderer() const{
		return _renderer;
	}

	int Context::width() const{
		return _width;
	}
	
	int Context::height() const{
		return _height;
	}
	
	void Context::width(int width){
		_width = ceil(width/2.0) * 2;
	}
	
	void Context::height(int height){
		_height = ceil(height/2.0) * 2;
	}

	void Context::loadMatrix(const Matrix4 &mat){
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat *)mat.array());
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void Context::loadMatrix3D(const Matrix4 &mat){
		loadMatrix(mat);
		glEnable(GL_CULL_FACE);
	}
	
	void Context::loadMatrix2D(const Matrix4 &mat){
		loadMatrix(mat);
		glDisable(GL_CULL_FACE);
	}

	void Context::begin(){
		_current = this;
		if(_width > 0 && _height > 0){
			glViewport(0, 0, _width, _height);
		}
		if(framebuffer()){
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer());
		}
		
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		// premultiplied alpha
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // LINEAR 使用平均算法，抗锯齿
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	
	void Context::clear(){
		clear(0, 0, 0, 0);
	}
	
	void Context::clear(float r, float g, float b, float a){
		clearColor(r, g, b, a);
		clearDepth();
	}

	void Context::clearColor(float r, float g, float b, float a){
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Context::clearDepth(){
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void Context::flush(){
		glFlush();
	}

	void Context::finish(){
		glFinish();
	}
	
	void Context::blit(GLuint dstFbo){
		if(framebuffer()){
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dstFbo);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer());
			glBlitFramebuffer(0, 0, (GLsizei)_width, (GLsizei)_height,
							  0, 0, (GLsizei)_width, (GLsizei)_height,
							  GL_COLOR_BUFFER_BIT, GL_NEAREST); // GL_LINEAR GL_NEAREST
			glBindFramebuffer(GL_READ_FRAMEBUFFER, dstFbo);
		}
	}

}; // end namespace
