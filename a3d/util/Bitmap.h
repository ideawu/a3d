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
		static Bitmap* createFromCGImage(const CGImageRef image, int width, int height);
		static Bitmap* createFromCGImageSourceAtIndex(const CGImageSourceRef imageSource, int index);

		int width() const;
		int height() const;
		char* pixels() const;
		
		// 调用者不可释放此对象
		CGContextRef CGContext();
		// 调用者不可释放此对象
		CGImageRef CGImage();
		bool savePNGFile(const char *filename);
		
	private:
		Bitmap();
		Bitmap(const Bitmap &d);
		Bitmap& operator =(const Bitmap &d);

		char *_pixels;
		int _width;
		int _height;
		
		CGContextRef _CGContext;
		CGImageRef _CGImage;
	};
}; // end namespace

#endif /* Bitmap_hpp */
