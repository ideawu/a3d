//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "GContext.h"
#include "GMemoryContext.h"

namespace a3d{
	GContext* GContext::memoryContext(float width, float height){
		GMemoryContext *impl = new GMemoryContext();
		impl->width(width);
		impl->height(height);
		impl->setup();
		return impl;
	}
	
	float GContext::width() const{
		return _width;
	}
	
	float GContext::height() const{
		return _height;
	}
	
	void GContext::width(float width){
		_width = (int)((double)width/2 + 0.5) * 2;
	}
	
	void GContext::height(float height){
		_height = (int)((double)height/2 + 0.5) * 2;
	}
	
	void GContext::bind3D(const Matrix4 &mat){
		glViewport(0, 0, _width, _height);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat *)mat.buffer());
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		// 2D和3D用的属性一般不同，所以每一次都设置一遍
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		{
			glFrontFace(GL_CW); // 将顺时针方向多边形设为正表面，符合上右下左惯例顺序
		}
		glDisable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		{
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glBindTexture(GL_TEXTURE_2D, 0); // 清空纹理
		}
		
		if(framebuffer()){
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer());
		}
	}

	void GContext::bind2D(const Matrix4 &mat){
		glViewport(0, 0, _width, _height);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat *)mat.buffer());
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		// 2D和3D用的属性一般不同，所以每一次都设置一遍
		glDisable(GL_MULTISAMPLE);
		//	glEnable(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		glEnable(GL_TEXTURE_2D);
		{
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glBindTexture(GL_TEXTURE_2D, 0); // 清空纹理
		}

		if(framebuffer()){
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer());
		}
	}
	
	void GContext::flush(){
		if(framebuffer()){
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer());
			glDrawBuffer(GL_BACK); // Set the back buffer as the draw buffer
			glBlitFramebuffer(0, 0, (GLsizei)_width, (GLsizei)_height,
							  0, 0, (GLsizei)_width, (GLsizei)_height,
							  GL_COLOR_BUFFER_BIT, GL_LINEAR); // GL_LINEAR GL_NEAREST
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		glFlush();
	}

}; // end namespace
