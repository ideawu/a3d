//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "BufferContext.h"

namespace a3d{
	
	BufferContext::BufferContext(){
		_framebuffer = 0;
		_colorbuffer = 0;
		_depthbuffer = 0;
	}
	
	BufferContext::~BufferContext(){
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
	
	GLuint BufferContext::framebuffer(){
		return _framebuffer;
	}

	void BufferContext::setup(){
		int width = this->width();
		int height = this->height();

		glGenFramebuffers(1, &_framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

		glGenRenderbuffers(1, &_colorbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, _colorbuffer);
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA, width, height);
		
		glGenRenderbuffers(1, &_depthbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, _depthbuffer);
//		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, width, height);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 3, GL_DEPTH_STENCIL, width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorbuffer);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthbuffer);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthbuffer);

		//GL_DRAW_FRAMEBUFFER
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
			fprintf(stderr, "frame buffer not complete");
			return;
		}
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		/*
		 // create memory storage for the pixel array
		 int image_bytes = alignInteger(render_width*3, BMP_ROW_ALIGN) * render_height;
		 unsigned char *image = new unsigned char[image_bytes];
		 
		 // copy pixels to memory from the single-sampled frame bffer
		 glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer); // set up to read from the single-sampled FBO
		 glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);               // do not copy into any server side buffer object
		 glReadBuffer(GL_COLOR_ATTACHMENT0);
		 glPixelStorei(GL_PACK_ALIGNMENT, BMP_ROW_ALIGN);
		 glGetError();
		 glReadPixels(0, 0, render_width, render_height,
		 GL_BGR, GL_UNSIGNED_BYTE, image);
		 GLenum error = checkGLError(__FILE__, __LINE__);
		 */
	}


}; // end namespace
