//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_ImageSprite_hpp
#define a3d_ImageSprite_hpp

#include <ImageIO/ImageIO.h>
#include <vector>
#include "Sprite.h"
#include "Bitmap.h"
#include "Texture.h"

namespace a3d{
	class ImageSprite : public Sprite
	{
	public:
		static ImageSprite* createFromFile(const char *filename);
		static ImageSprite* createFromBitmap(const Bitmap &bitmap);

		virtual ~ImageSprite();
		virtual int frameAtTime(double time, double *duration);
		virtual Texture* textureAtTime(double time, double *duration);
		virtual Texture* textureAtFrame(int frame, double *duration);

	private:
		ImageSprite();
		ImageSprite(const ImageSprite &d);
		ImageSprite& operator =(const ImageSprite &d);
		
		Texture *_texture;
		std::vector<double> _durations;
		CGImageSourceRef _cgimgSrc;
		
		void loadFromFile(const char *filename);
	};
}; // end namespace

#endif /* ImageSprite_hpp */
