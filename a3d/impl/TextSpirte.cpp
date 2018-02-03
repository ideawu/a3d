//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "TextSpirte.h"
#include "Text.h"
#include "Bitmap.h"
#include "Renderer.h"

namespace a3d{

	TextSprite* TextSprite::create(const char *str){
		Text text(str);
		Bitmap *bitmap = text.drawToBitmap();
		if(!bitmap){
			return NULL;
		}
		GLint tid = Renderer::current()->createTexture(bitmap->pixels(), bitmap->width(), bitmap->height());
		TextSprite *ret = new TextSprite();
		ret->_tid = tid;
		return ret;
	}

	TextSprite::TextSprite(){
		frames(0);
		duration(0);
		_tid = 0;
	}
	
	TextSprite::~TextSprite(){
	}

	int TextSprite::frameAtTime(double time, double *duration){
		return 0;
	}
	
	GLuint TextSprite::textureAtTime(double time, double *duration){
		return _tid;
	}
	
	GLuint TextSprite::textureAtFrame(int frame, double *duration){
		return _tid;
	}

}; // end namespace

