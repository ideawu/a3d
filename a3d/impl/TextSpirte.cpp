//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "TextSpirte.h"
#include "Text.h"
#include "Bitmap.h"
#include "Renderer.h"

namespace a3d{

	TextSprite* TextSprite::create(const char *str){
		return TextSprite::create(str, 0, Color::white());
	}

	TextSprite* TextSprite::create(const char *str, float fontSize, const Color &fontColor){
		Text text(str);
		if(fontSize > 0){
			text.fontSize(fontSize);
		}
		text.fontColor(fontColor);
		
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
		ret->frames(1);
		ret->width(bitmap->width());
		ret->height(bitmap->height());
		
		delete bitmap;
		return ret;
	}

	TextSprite::TextSprite():Sprite(){
		_texture = NULL;
	}
	
	TextSprite::~TextSprite(){
		delete _texture;
	}

	int TextSprite::frameAtTime(double time, double *duration){
		if(duration){
			*duration = 0;
		}
		return 0;
	}
	
	Texture* TextSprite::textureAtTime(double time, double *duration){
		if(duration){
			*duration = 0;
		}
		return _texture;
	}
	
	Texture* TextSprite::textureAtFrame(int frame, double *duration){
		if(duration){
			*duration = 0;
		}
		return _texture;
	}

}; // end namespace

