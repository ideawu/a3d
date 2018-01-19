//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef DraftImage_hpp
#define DraftImage_hpp

#include "Node.h"
#include "Texture.h"

class DraftImage : public a3d::Node
{
public:
	~DraftImage();
	DraftImage(const char *filename);
	virtual void draw();
	void scale(float xyz);
	void scale(float x, float y, float z);
private:
	DraftImage();
	a3d::Texture *_texture;
};

#endif /* DraftImage_hpp */
