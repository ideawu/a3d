//  Created by ideawu on 2019/2/10.
//  Copyright © 2019 ideawu. All rights reserved.
//

#include "GLContext.h"
#include <pthread.h>

static pthread_key_t _pthread_key;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

namespace a3d{
	
	GLContext* GLContext::createShared(){
		GLContext *ret = new GLContext();
		ret->_CGLContext = CGLGetCurrentContext();
		ret->makeCurrent();
		return ret;
	}
	
	GLContext* GLContext::create(){
		CGLPixelFormatAttribute attributes[] = {
			kCGLPFANoRecovery,
			kCGLPFAAccelerated,
			kCGLPFADoubleBuffer,
			kCGLPFAColorSize, (CGLPixelFormatAttribute)24,
			kCGLPFADepthSize, (CGLPixelFormatAttribute)16,
			kCGLPFAAlphaSize, (CGLPixelFormatAttribute)8,
			kCGLPFAStencilSize, (CGLPixelFormatAttribute)8,
			(CGLPixelFormatAttribute) 0
		};
		
		CGLContextObj context = NULL;
		CGLPixelFormatObj pix = NULL;
		CGLError error;
		GLint num;
		error = CGLChoosePixelFormat(attributes, &pix, &num);
		if(error){
			log_error("create pixel format error: %d", error);
		}else{
			error = CGLCreateContext(pix, NULL, &context);
			if(error){
				log_error("create context error: %d", error);
			}
			CGLDestroyPixelFormat(pix);
		}
		if(!context){
			return NULL;
		}

		GLContext *ret = new GLContext();
		ret->_CGLContext = context;
		ret->makeCurrent();
		return ret;
	}

	static void thread_init() {
		pthread_key_create(&_pthread_key, NULL);
	}
	
	GLContext::GLContext(){
		pthread_once(&init_once, thread_init);
		_CGLContext = NULL;
		_isShared = false;
		_renderer = new Renderer();
	}

	GLContext::~GLContext(){
		CGLSetCurrentContext(NULL);
		if(!_isShared){
			CGLDestroyContext(_CGLContext);
		}
		delete _renderer;
	}

	Renderer* GLContext::renderer() const{
		return _renderer;
	}

	void GLContext::makeCurrent(){
		pthread_setspecific(_pthread_key, this);
		CGLError error = CGLSetCurrentContext(_CGLContext);
		if(error){
			log_error("set current ontext error: %d", error);
		}
	}

	GLContext* GLContext::current(){
		GLContext *ctx = (GLContext *)pthread_getspecific(_pthread_key);
		return ctx;
	}
	
}; // end namespace
