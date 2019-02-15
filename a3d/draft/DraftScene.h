// Created by ideawu on 03/01/2018.
// Copyright © 2018 ideawu. All rights reserved.
//
// 画简单的3D空间，测试用。

#ifndef DRAFT_SCENE_H
#define DRAFT_SCENE_H

#include "Node.h"

class DraftScene : public a3d::Node
{
public:
	DraftScene(){}
	virtual void draw();
};

#endif
