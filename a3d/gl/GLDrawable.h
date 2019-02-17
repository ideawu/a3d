//  Created by ideawu on 2019/2/10.
//  Copyright © 2019 ideawu. All rights reserved.
//

#ifndef GLDrawable_hpp
#define GLDrawable_hpp

#include "Bitmap.h"

namespace a3d{
	class GLDrawable
	{
	public:
		// 创建一个空的画板，基于当前 FBO
		static GLDrawable* blank();
		// width, height 不是偶数，会导致blit少一行，所以会自动转成偶数。
		// 注意：如果 samples 大于 0，bitmap 将不可用。
		static GLDrawable* create(int width, int height, int samples);

		int width() const;
		int height() const;
		int samples() const;

		void begin();
		void clear();
		void clear(float r, float g, float b, float a=1);
		void clearColor(float r, float g, float b, float a=1);
		void clearDepth();
		
		void blit(GLuint dstFbo);
		void blit(GLDrawable *buffer=NULL);

		void flush();
		void finish();
		
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
		
		void setupFBO();

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
