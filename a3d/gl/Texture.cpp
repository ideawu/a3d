//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Texture.h"

namespace a3d{
	
	Texture* Texture::createFromBitmap(const Bitmap &bitmap){
		Texture *ret = new Texture();
		ret->loadBitmap(bitmap);
		if(ret->name() == 0){
			delete ret;
			return NULL;
		}
		return ret;
	}
	
	Texture::Texture(){
		_tid = 0;
	}

	Texture::~Texture(){
		if(_tid){
			glDeleteTextures(1, &_tid);
		}
	}

	GLuint Texture::name() const{
		return _tid;
	}
	
	void Texture::bind(){
		glBindTexture(GL_TEXTURE_2D, _tid);
	}
	
	void Texture::unbind(){
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::loadBitmap(const Bitmap &bitmap){
		if(_tid){
			glDeleteTextures(1, &_tid);
		}
		
		int width = bitmap.width();
		int height = bitmap.height();
		const char *pixels = bitmap.pixels();
		
		glGenTextures(1, &_tid);
//		log_debug("%d", tid);
		if(!_tid){
			return;
		}
		glBindTexture(GL_TEXTURE_2D, _tid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // LINEAR 使用平均算法，抗锯齿
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::draw(const Rect &texRect, const Rect vertRect){
		if(!name()){
			return;
		}
		
		float tx0 = texRect.x;
		float ty0 = texRect.y;
		float tx1 = texRect.x + texRect.width;
		float ty1 = texRect.y + texRect.height;
		
		float vx0 = vertRect.x;
		float vy0 = vertRect.y;
		float vx1 = vertRect.x + vertRect.width;
		float vy1 = vertRect.y + vertRect.height;
		float z = 0;

		bind();
		glDisable(GL_CULL_FACE);
		glBegin(GL_POLYGON);
		{
			glTexCoord2f(tx0, ty0); glVertex3f(vx0, vy0, z);
			glTexCoord2f(tx1, ty0); glVertex3f(vx1, vy0, z);
			glTexCoord2f(tx1, ty1); glVertex3f(vx1, vy1, z);
			glTexCoord2f(tx0, ty1); glVertex3f(vx0, vy1, z);
		}
		glEnd();
		glEnable(GL_CULL_FACE);
		unbind();
	}

}; // end namespace
