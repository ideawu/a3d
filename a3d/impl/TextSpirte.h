//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_TextSpirte_hpp
#define a3d_TextSpirte_hpp

#include "Sprite.h"
#include "Color.h"

namespace a3d{
	class TextSprite : public Sprite
	{
	public:
		static TextSprite* create(const char *str);
		static TextSprite* create(const char *str, float fontSize, const Color &fontColor);

		virtual ~TextSprite();
		virtual int frameAtTime(double time, double *duration);
		virtual Texture* textureAtTime(double time, double *duration);
		virtual Texture* textureAtFrame(int frame, double *duration);
		
	private:
		TextSprite();
		TextSprite(const TextSprite &d);
		TextSprite& operator =(const TextSprite &d);
		
		Texture *_texture;
	};
}; // end namespace

#endif /* TextSpirte_hpp */
