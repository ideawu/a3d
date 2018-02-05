//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Bitmap_hpp
#define a3d_Bitmap_hpp

#include <ImageIO/ImageIO.h>

namespace a3d{
	class Bitmap
	{
	public:
		~Bitmap();

		static Bitmap* create(int width, int height);
		static Bitmap* createWithPixels(char *pixels, int width, int height);
		static Bitmap* createFromCGImage(const CGImageRef image);
		static Bitmap* createFromCGImageSourceAtIndex(const CGImageSourceRef imageSource, int index);

		int width() const;
		int height() const;
		char* pixels() const;
		
		CGImageRef createCGImage();
		bool savePNGFile(const char *filename);
		
	private:
		Bitmap();
		Bitmap(const Bitmap &d);
		Bitmap& operator =(const Bitmap &d);

		char *_pixels;
		int _width;
		int _height;
	};
}; // end namespace

#endif /* Bitmap_hpp */
