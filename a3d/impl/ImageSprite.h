//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef ImageSprite_hpp
#define ImageSprite_hpp

#include <ImageIO/ImageIO.h>
#include <vector>
#include "Sprite.h"

namespace a3d{
	class ImageSprite : public Sprite
	{
	public:
		static ImageSprite* create(const char *filename);
		
		virtual ~ImageSprite();
		virtual int frameAtTime(double time, double *duration);
		virtual Texture* textureAtTime(double time, double *duration);
		virtual Texture* textureAtFrame(int frame, double *duration);

	private:
		ImageSprite();
		ImageSprite(const ImageSprite &d);
		ImageSprite& operator =(const ImageSprite &d);
		
		std::vector<Texture *> _textures;
		std::vector<double> _durations;
		CGImageSourceRef _cgimgSrc;
	};
}; // end namespace

#endif /* ImageSprite_hpp */
