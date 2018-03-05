//  Created by ideawu on 04/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//
// 一个简单的带有头和身体的角色。

#ifndef DRAFT_SPRITE_H
#define DRAFT_SPRITE_H

#include "Node.h"
#include "Color.h"

class DraftSprite : public a3d::Node
{
public:
	a3d::Color color;
	DraftSprite();
	virtual void drawAtTime(double time);

private:
	
	void drawHead();
	void drawBody();
};

#endif

