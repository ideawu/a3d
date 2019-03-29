//  Created by ideawu on 3/29/19.
//  Copyright © 2019 ideawu. All rights reserved.
//

#include "TextureNode.h"
#include "Frame.h"

namespace a3d{
	
	TextureNode* TextureNode::create(int width, int height){
		Texture *texture = Texture::create(width, height);
		if(!texture){
			return NULL;
		}
		TextureNode *ret = new TextureNode();
		ret->_texture = texture;
		return ret;
	}
	
	TextureNode* TextureNode::createFromBitmap(const Bitmap *bitmap){
		Texture *texture = Texture::createFromBitmap(bitmap);
		if(!texture){
			return NULL;
		}
		TextureNode *ret = new TextureNode();
		ret->_texture = texture;
		return ret;
	}

	TextureNode::TextureNode(){
		_texture = NULL;
	}
	
	TextureNode::~TextureNode(){
		delete _texture;
	}

	Texture* TextureNode::texture() const{
		return _texture;
	}

	void TextureNode::draw(){
		if(_texture){
			Frame texRect = Frame(0, 0, 1, 1);
			Frame verRect = Frame(-_texture->width()/2, -_texture->height()/2, _texture->width(), _texture->height());
			_texture->draw(texRect, verRect);
		}
	}

}; // end namespace
