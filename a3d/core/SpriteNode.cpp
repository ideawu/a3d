//  Created by ideawu on 18-1-28.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#include "SpriteNode.h"
#include "Sprite.h"

namespace a3d{

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

}; // end namespace
