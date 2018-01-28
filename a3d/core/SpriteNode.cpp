//  Created by ideawu on 18-1-28.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#include "SpriteNode.h"

namespace a3d{

	SpriteNode::SpriteNode(){
		_sprite = NULL;
		_contentNode = new Node();
		this->addSubNode(_contentNode);
		_isFrameLossless = true;
		_isLooping = true;
	}

	SpriteNode::~SpriteNode(){
		delete _sprite;
		delete _contentNode;
	}

	Node* SpriteNode::contentNode() const{
		return _contentNode;
	}

	Sprite* SpriteNode::sprite() const{
		return _sprite;
	}

	void SpriteNode::sprite(Sprite *sprite){
		if(_sprite){
			delete _sprite;
		}
		_sprite = sprite;
	}

	void SpriteNode::isFrameLossless(bool isLossless){
		_isFrameLossless = isLossless;
	}

	void SpriteNode::isLooping(bool looping){
		_isLooping = looping;
	}
	
}; // end namespace
