//
//  MySprite.h
//  Test
//
//  Created by ideawu on 05/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "a3d/a3d.h"

class MySprite : public a3d::Node
{
public:
	MySprite(){sprite = NULL;}
	virtual void draw();
	a3d::Sprite *sprite;
};

