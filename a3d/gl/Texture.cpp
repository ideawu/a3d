//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Texture.h"

namespace a3d{
	
	int Texture::texture_count = 0;

	Texture* Texture::create(int width, int height){
		Bitmap *bitmap = Bitmap::create(width, height);
		if(!bitmap){
			return NULL;
		}
		Texture *ret = Texture::createFromBitmap(bitmap);
		delete bitmap;
		return ret;
	}

	Texture* Texture::createFromBitmap(const Bitmap *bitmap){
		Texture *ret = new Texture();
		ret->_size = Vector3(bitmap->width(), bitmap->height(), 0);
		ret->loadBitmap(bitmap);
		if(ret->name() == 0){
			delete ret;
			return NULL;
		}
		return ret;
	}
	
	Texture::Texture(){
		_tid = 0;
//		log_debug("create %d", this);
	}

	Texture::~Texture(){
		if(_tid){
			glDeleteTextures(1, &_tid);
//			log_debug("del tid: %d, textures: %d", _tid, --texture_count);
		}
//		log_debug("delete %d", this);
	}
	
	Vector3 Texture::size() const{
		return _size;
	}
	
	float Texture::width() const{
		return _size.w;
	}
	
	float Texture::height() const{
		return _size.h;
	}

	GLuint Texture::name() const{
		return _tid;
	}
	
	void Texture::bind() const{
		glBindTexture(GL_TEXTURE_2D, _tid);
	}
	
	void Texture::unbind() const{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::loadBitmap(const Bitmap *bitmap){
		bool isNew = (_tid == 0);
		if(isNew){
			glGenTextures(1, &_tid);
			// log_debug("gen tid: %d, textures: %d", _tid, ++texture_count);
			if(!_tid){
				log_error("glGenTextures failed!");
				return;
			}
		}

		GLsizei width = bitmap->width();
		GLsizei height = bitmap->height();
		const char *pixels = bitmap->pixels();
		
		glBindTexture(GL_TEXTURE_2D, _tid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // LINEAR 使用平均算法，抗锯齿
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		if(isNew){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pixels);
		}else{
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pixels);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::draw(const Frame &texRect, const Frame verRect) const{
		if(!name()){
			return;
		}

		float tx0 = texRect.x;
		float ty0 = texRect.y;
		float tx1 = tx0 + texRect.width;
		float ty1 = ty0 + texRect.height;
		
		float vx0 = verRect.x;
		// flip y
		float vy0 = verRect.y + verRect.height;
		float vx1 = vx0 + verRect.width;
		float vy1 = vy0 - verRect.height;
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
