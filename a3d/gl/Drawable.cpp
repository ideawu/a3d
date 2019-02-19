//  Created by ideawu on 2019/2/10.
//  Copyright © 2019 ideawu. All rights reserved.
//

#include "Drawable.h"

namespace a3d{
	Drawable* Drawable::createShared(){
		Drawable *ret = new Drawable();
		ret->_isShared = true;
//		GLint drawFbo = 0;
//		glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFbo);
//		ret->_framebuffer = drawFbo;
		return ret;
	}

	Drawable* Drawable::create(int width, int height, int samples){
		Drawable *impl = new Drawable();
		impl->width(width);
		impl->height(height);
		impl->samples(samples);
		impl->setupFBO();
		return impl;
	}

	Drawable::Drawable(){
		_isShared = false;
		_framebuffer = 0;
		_colorbuffer = 0;
		_depthbuffer = 0;
		_samples = 0;
		_bitmap = NULL;
	}
	
	Drawable::~Drawable(){
		if(!_isShared){
			if(_framebuffer){
				glDeleteFramebuffers(1, &_framebuffer);
			}
			if(_colorbuffer){
				glDeleteRenderbuffers(1, &_colorbuffer);
			}
			if(_depthbuffer){
				glDeleteRenderbuffers(1, &_depthbuffer);
			}
		}
		delete _bitmap;
	}

	int Drawable::width() const{
		return _width;
	}
	
	void Drawable::width(int width){
		_width = ceil(width/2.0) * 2;
	}

	int Drawable::height() const{
		return _height;
	}
	
	void Drawable::height(int height){
		_height = ceil(height/2.0) * 2;
	}
	
	int Drawable::samples() const{
		return _samples;
	}
	
	void Drawable::samples(int samples){
		_samples = samples;
	}

	
	void Drawable::setupFBO(){
		int width = this->width();
		int height = this->height();
		
		glGenFramebuffers(1, &_framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
		
		glGenRenderbuffers(1, &_colorbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, _colorbuffer);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, _samples, GL_RGBA, width, height);
		
		glGenRenderbuffers(1, &_depthbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, _depthbuffer);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, _samples, GL_DEPTH_STENCIL, width, height);
		
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorbuffer);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthbuffer);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthbuffer);
		
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
			log_error("frame buffer not complete");
			return;
		}
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void Drawable::begin(){
		if(_width > 0 && _height > 0){
			// glViewport 逻辑上不属于"相机"
			glViewport(0, 0, _width, _height);
		}
		if(_framebuffer){
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
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
	
	void Drawable::clear(){
		clear(0, 0, 0, 0);
	}
	
	void Drawable::clear(float r, float g, float b, float a){
		clearColor(r, g, b, a);
		clearDepth();
	}

	void Drawable::clearColor(const Color &color){
		clearColor(color.r, color.g, color.b, color.a);
	}

	void Drawable::clearColor(float r, float g, float b, float a){
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void Drawable::clearDepth(){
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	
	void Drawable::flush(){
		glFlush();
	}
	
	void Drawable::finish(){
		glFinish();
	}
	
	void Drawable::blit(Drawable *buffer){
		GLuint dstFbo = buffer? buffer->_framebuffer : 0;
		this->blit(dstFbo);
	}

	void Drawable::blit(GLuint dstFbo){
		if(_isShared){ // TODO:
			return;
		}
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dstFbo);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, _framebuffer);
		glBlitFramebuffer(0, 0, (GLsizei)_width, (GLsizei)_height,
						  0, 0, (GLsizei)_width, (GLsizei)_height,
						  GL_COLOR_BUFFER_BIT, GL_NEAREST); // GL_LINEAR GL_NEAREST
		glBindFramebuffer(GL_READ_FRAMEBUFFER, dstFbo);
	}

	Bitmap* Drawable::bitmap(){
		if(!_bitmap){
			_bitmap = Bitmap::create(_width, _height);
		}

		// 如果 framebuffer 是 multisampled，那么 glReadPixels() 将报错。
		// https://www.khronos.org/opengl/wiki/GL_EXT_framebuffer_multisample
		if(_framebuffer){
			glBindFramebuffer(GL_READ_FRAMEBUFFER, _framebuffer);
		}
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glReadPixels(0, 0, _width, _height, GL_BGRA, GL_UNSIGNED_BYTE, _bitmap->pixels());
		
		return _bitmap;
	}
}; // end namespace
