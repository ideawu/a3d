//  Created by ideawu on 08/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef TextureSprite_hpp
#define TextureSprite_hpp

#include "Sprite.h"

namespace a3d{
	class TextureSprite : public Sprite
	{
	public:
		TextureSprite();
		virtual ~TextureSprite();
		virtual int frameAtTime(double time, double *duration);
		virtual Texture* textureAtTime(double time, double *duration);
		virtual Texture* textureAtFrame(int frame, double *duration);

		// 内存由 TextureSprite 管理
		void texture(Texture *texture);

	private:
		TextureSprite(const TextureSprite &d);
		TextureSprite& operator =(const TextureSprite &d);
		
		Texture *_texture;
	};
}; // end namespace

#endif /* EmptySprite_hpp */
