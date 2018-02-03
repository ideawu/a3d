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
		Texture *texture = Texture::createFromBitmap(*bitmap);
		if(!texture){
			delete bitmap;
			return NULL;
		}
		
		TextSprite *ret = new TextSprite();
		ret->_texture = texture;
		ret->width(bitmap->width());
		ret->height(bitmap->height());

		delete bitmap;
		return ret;
	}

	TextSprite::TextSprite(){
		frames(0);
		duration(0);
		_texture = NULL;
	}
	
	TextSprite::~TextSprite(){
		delete _texture;
	}

	int TextSprite::frameAtTime(double time, double *duration){
		return 0;
	}
	
	Texture* TextSprite::textureAtTime(double time, double *duration){
		return _texture;
	}
	
	Texture* TextSprite::textureAtFrame(int frame, double *duration){
		return _texture;
	}

}; // end namespace

