//  Created by ideawu on 2019/2/10.
//  Copyright © 2019 ideawu. All rights reserved.
//

#include "Context.h"
#include <pthread.h>

static pthread_key_t _pthread_key;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

namespace a3d{
	static CGLContextObj createCGLContext();

	Context* Context::createShared(){
		Context *ret = new Context();
		ret->_isShared = true;
		ret->_CGLContext = CGLGetCurrentContext();
		ret->makeCurrent();
		return ret;
	}

	Context* Context::create(){
		CGLContextObj cglcontext = createCGLContext();
		if(!cglcontext){
			return NULL;
		}

		Context *ret = new Context();
		ret->_CGLContext = cglcontext;
		ret->makeCurrent();
		return ret;
	}

	static void thread_init() {
		pthread_key_create(&_pthread_key, NULL);
	}
	
	Context::Context(){
		pthread_once(&init_once, thread_init);
		_CGLContext = NULL;
		_isShared = false;
		_renderer = new Renderer();
	}

	Context::~Context(){
		CGLSetCurrentContext(NULL);
		if(!_isShared){
			CGLDestroyContext(_CGLContext);
		}
		delete _renderer;
	}

	Renderer* Context::renderer() const{
		return _renderer;
	}

	void Context::makeCurrent(){
		pthread_setspecific(_pthread_key, this);
		if(!_isShared){
			CGLError error = CGLSetCurrentContext(_CGLContext);
			if(error){
				log_error("set current ontext error: %d", error);
			}
		}
	}

	Context* Context::current(){
		Context *ctx = (Context *)pthread_getspecific(_pthread_key);
		return ctx;
	}

	static CGLContextObj createCGLContext(){
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
		return context;
	}
}; // end namespace
