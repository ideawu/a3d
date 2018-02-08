//  Created by ideawu on 08/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef TextureNode_hpp
#define TextureNode_hpp

#include "Node.h"
#include "Texture.h"

namespace a3d{
	class TextureNode : public Node
	{
	public:
		TextureNode();
		virtual ~TextureNode();
		virtual void drawAtTime(double time);
		
		// 注意，texture内存不由TextureNode管理
		void texture(const Texture *texture);

	private:
		TextureNode(const TextureNode &d);
		TextureNode& operator =(const TextureNode &d);
		
		const Texture *_texture;
	};
}; // end namespace

#endif /* TextureNode_hpp */
