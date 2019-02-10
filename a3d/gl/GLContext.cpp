//  Created by ideawu on 2019/2/10.
//  Copyright © 2019 ideawu. All rights reserved.
//

#include "GLContext.h"

namespace a3d{
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
		error = CGLSetCurrentContext(context);
		if(error){
			log_error("set current ontext error: %d", error);
		}

		GLContext *ret = new GLContext();
		ret->_CGLContext = context;
		return ret;
	}

	GLContext::GLContext(){
		_CGLContext = NULL;
	}

	GLContext::~GLContext(){
		CGLSetCurrentContext(NULL);
		CGLDestroyContext(_CGLContext);
	}

	void GLContext::bind(){
		CGLSetCurrentContext(_CGLContext);
	}

}; // end namespace
