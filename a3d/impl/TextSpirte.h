//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef TextSpirte_hpp
#define TextSpirte_hpp

#include "Sprite.h"
#include <vector>

namespace a3d{
	class TextSprite : public Sprite
	{
	public:
		static TextSprite* create(const char *text);
		
		virtual ~TextSprite();
		virtual int frameAtTime(double time, double *duration);
		virtual GLuint textureAtTime(double time, double *duration);
		virtual GLuint textureAtFrame(int frame, double *duration);
		
	private:
		TextSprite();
		TextSprite(const TextSprite &d);
		TextSprite& operator =(const TextSprite &d);
	};
}; // end namespace

#endif /* TextSpirte_hpp */
