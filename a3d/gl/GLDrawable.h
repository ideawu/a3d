//  Created by ideawu on 2019/2/10.
//  Copyright © 2019 ideawu. All rights reserved.
//

#ifndef GLDrawable_hpp
#define GLDrawable_hpp

namespace a3d{
	class Bitmap;
	
	class GLDrawable
	{
	public:
		// width, height 不是偶数，会导致blit少一行，所以会自动转成偶数。
		static GLDrawable* create(int width, int height, int samples);

		int width() const;
		int height() const;
		int samples() const;

		void begin();
		void clear();
		void clear(float r, float g, float b, float a=1);
		void clearColor(float r, float g, float b, float a=1);
		void clearDepth();
		void flush();
		void finish();
		void blit(GLDrawable *buffer=NULL);
		
		// 调用者不可释放此对象
		Bitmap* bitmap();

		~GLDrawable();
		
	private:
		GLDrawable();
		GLDrawable(const GLDrawable &d);
		GLDrawable& operator =(const GLDrawable &d);

		void width(int width);
		void height(int height);
		void samples(int samples);
		
		void setup();

		int _width;
		int _height;
		int _samples;
		
		GLuint _framebuffer;
		GLuint _colorbuffer;
		GLuint _depthbuffer;

		Bitmap *_bitmap;
	};
}; // end namespace

#endif /* GLDrawable_hpp */
