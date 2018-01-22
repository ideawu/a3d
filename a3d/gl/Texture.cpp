//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Texture.h"

namespace a3d{
	Texture::Texture(){
		_id = 0;
	}
	
	Texture::~Texture(){
		if(_id){
			glDeleteTextures(1, &_id);
		}
	}

	Texture* Texture::textureFromImageFile(const char *filename){
		Texture *ret = new Texture();
		if(ret->loadImageFile(filename) == -1){
			delete ret;
			return NULL;
		}
		return ret;
	}

	GLuint Texture::id() const{
		return _id;
	}
	
	void Texture::id(GLuint i){
		_id = i;
	}

	Vector3 Texture::size() const{
		return Vector3(_width, _height, 0);
	}

	int Texture::width() const{
		return _width;
	}
	
	void Texture::width(int w){
		_width = w;
	}
	
	int Texture::height() const{
		return _height;
	}

	void Texture::height(int h){
		_height = h;
	}

	int Texture::loadImageFile(const char *filename){
		char *data = load_image_data(filename, &_width, &_height);
		if(!data){
			return -1;
		}
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // LINEAR 使用平均算法，搞锯齿
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)_width, (GLsizei)_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
		free(data);
		return 0;
	}

}; // end namespace
