//  Created by ideawu on 3/29/19.
//  Copyright © 2019 ideawu. All rights reserved.
//

#ifndef a3d_TextureNode_hpp
#define a3d_TextureNode_hpp

#include "Node.h"
#include "Texture.h"

namespace a3d{
	class TextureNode : public Node
	{
	public:
		static TextureNode* create(int width, int height);
		static TextureNode* createFromBitmap(const Bitmap *bitmap);
		
		virtual ~TextureNode();
		
		virtual void draw();
		virtual void updateAtTime(double time);
		
		Texture* texture() const;

	private:
		TextureNode();
		TextureNode(const TextureNode &d);
		TextureNode& operator =(const TextureNode &d);

		Texture *_texture;
	};
};
	
#endif /* TextureNode_hpp */
