//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef ImageSprite_hpp
#define ImageSprite_hpp

#include "Sprite.h"
//#include <ImageIO/CGImageSource.h>
#include <ImageIO/ImageIO.h>
#include <vector>

namespace a3d{
	class ImageSprite : public Sprite
	{
	public:
		static ImageSprite* create(const char *filename);
		
		virtual ~ImageSprite();
		// TODO
		virtual int frameAtTime(float time, float *duration){return 0;}
		virtual GLuint textureAtFrame(int frame, float *duration);
		virtual GLuint textureAtTime(float time, float *duration);

	private:
		ImageSprite();
		ImageSprite(const ImageSprite &d);
		ImageSprite& operator =(const ImageSprite& d);
		
		GLuint bindImageData(const char *data, int width, int height);
		
		std::vector<GLuint> _texIdAtFrame;
		std::vector<float> _durations;
		CGImageSourceRef _cgimgSrc;
	};
}; // end namespace

#endif /* ImageSprite_hpp */
