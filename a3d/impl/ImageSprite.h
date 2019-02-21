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
		static ImageSprite* createFromBitmap(const Bitmap *bitmap);
		static ImageSprite* createWithTexture(Texture *texture);
		static ImageSprite* createWithCGImageSource(CGImageSourceRef imgSource);

		virtual ~ImageSprite();
		virtual int frameAtTime(double time, double *duration);
		virtual Texture* textureAtTime(double time, double *duration);
		virtual Texture* textureAtFrame(int frame, double *duration);

		void addTexture(Texture *texture, double duration);
		// 解析图片，不涉及 OpenGL 操作
		void loadImageAtFrame(int frame);
		
	private:
		ImageSprite();
		ImageSprite(const ImageSprite &d);
		ImageSprite& operator =(const ImageSprite &d);
		
		// 不要重复利用 texture，因为解码GIF耗CPU，用VRAM换CPU
		std::vector<Texture*> _textures;
		std::vector<Bitmap *> _bitmaps;
		std::vector<double> _durations;
		CGImageSourceRef _cgimgSrc;
		
		void loadWithCGImageSource(CGImageSourceRef imgSource);
	};
}; // end namespace

#endif /* ImageSprite_hpp */
