//  Created by ideawu on 28/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GFrame.h"

@interface GFrame(){
	GLuint _framebuffer;
	GLuint _colorbuffer;
	GLuint _depthbuffer;
}
@end

@implementation GFrame

- (id)initWithWidth:(int)width height:(int)height{
	self = [super init];
	// 如果 width, height 不是偶数，会导致blit少一行，所以转成偶数。
	_width = (int)((double)width/2 + 0.5) * 2;
	_height = (int)((double)height/2 + 0.5) * 2;
	_framebuffer = 0;
	_colorbuffer = 0;
	_depthbuffer = 0;
	[self setup];
	return self;
}

- (void)dealloc{
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
	
- (void)setup{
	glGenRenderbuffers(1, &_colorbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, _colorbuffer);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, (GLsizei)_width, (GLsizei)_height);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA, (GLsizei)_width, (GLsizei)_height);

	glGenRenderbuffers(1, &_depthbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, _depthbuffer);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (GLsizei)_width, (GLsizei)_height);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, (GLsizei)_width, (GLsizei)_height);

	glGenFramebuffers(1, &_framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorbuffer);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthbuffer);

	if(glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		fprintf(stderr, "frame buffer not complete");
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/*
	// create memory storage for the pixel array
	int image_bytes = alignInteger(render_width*3, BMP_ROW_ALIGN) * render_height;
	unsigned char *image = new unsigned char[image_bytes];
	
	// copy pixels to memory from the single-sampled frame bffer
	glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);    // set up to read from the single-sampled FBO
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);                  // do not copy into any server side buffer object
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glPixelStorei(GL_PACK_ALIGNMENT, BMP_ROW_ALIGN);
	glGetError();
	glReadPixels(0, 0, render_width, render_height,
				 GL_BGR, GL_UNSIGNED_BYTE, image);
	GLenum error = checkGLError(__FILE__, __LINE__);
	 */
}

- (void)bind{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _framebuffer);
}

- (void)flush{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _framebuffer);
	glDrawBuffer(GL_BACK); // Set the back buffer as the draw buffer
	glBlitFramebuffer(0, 0, (GLsizei)_width, (GLsizei)_height,
					  0, 0, (GLsizei)_width, (GLsizei)_height,
					  GL_COLOR_BUFFER_BIT, GL_LINEAR); // GL_LINEAR GL_NEAREST
	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
	glFinish();
}



@end
