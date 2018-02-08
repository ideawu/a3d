//  Created by ideawu on 08/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "TextureSprite.h"

namespace a3d{
	
	TextureSprite::TextureSprite():Sprite(){
		_texture = NULL;
	}
	
	TextureSprite::~TextureSprite(){
		delete _texture;
	}
	
	void TextureSprite::texture(Texture *texture){
		if(_texture){
			delete _texture;
		}
		_texture = texture;
		this->width(texture->width());
		this->height(texture->height());
	}
	
	int TextureSprite::frameAtTime(double time, double *duration){
		if(duration){
			*duration = 0;
		}
		return 0;
	}
	
	Texture* TextureSprite::textureAtTime(double time, double *duration){
		if(duration){
			*duration = 0;
		}
		return _texture;
	}
	
	Texture* TextureSprite::textureAtFrame(int frame, double *duration){
		if(duration){
			*duration = 0;
		}
		return _texture;
	}

}; // end namespace
