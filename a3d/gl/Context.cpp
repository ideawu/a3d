//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Context.h"
#include "MemoryContext.h"

namespace a3d{
	Context* Context::memoryContext(float width, float height){
		MemoryContext *impl = new MemoryContext();
		impl->width(width);
		impl->height(height);
		impl->setup();
		return impl;
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
	
	void Context::bind(){
		glViewport(0, 0, _width, _height);
		if(framebuffer()){
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer());
		}
	}
	
	void Context::clear(){
		clear(0, 0, 0, 1);
	}
	
	void Context::clear(float r, float g, float b, float a){
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	
	void Context::loadMatrix(const Matrix4 &mat){
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat *)mat.matrix());
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	
	void Context::setupCamera3D(const Camera *camera){
		loadMatrix(camera->matrix3D());
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
	}

	void Context::setupCamera2D(const Camera *camera){
		loadMatrix(camera->matrix2D());
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
	}
	
	void Context::finish(){
		if(framebuffer()){
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer());
			glBlitFramebuffer(0, 0, (GLsizei)_width, (GLsizei)_height,
							  0, 0, (GLsizei)_width, (GLsizei)_height,
							  GL_COLOR_BUFFER_BIT, GL_LINEAR); // GL_LINEAR GL_NEAREST
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		glFinish();
	}

}; // end namespace
