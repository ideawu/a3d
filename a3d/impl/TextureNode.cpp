//  Created by ideawu on 08/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "TextureNode.h"

namespace a3d{

	TextureNode::TextureNode(){
		_texture = NULL;
	}
	
	TextureNode::~TextureNode(){
	}
	
	void TextureNode::texture(const Texture *texture){
		_texture = texture;
	}

	void TextureNode::drawAtTime(double time){
		if(_texture){
			Rect texRect = Rect(0, 0, 1, 1);
			Rect vertRect = Rect(-this->width()/2, -this->height()/2, this->width(), this->height());
			_texture->draw(texRect, vertRect);
		}
	}
}; // end namespace
