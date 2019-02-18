//  Created by ideawu on 2019/2/10.
//  Copyright © 2019 ideawu. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include "Bitmap.h"

namespace a3d{
	class Drawable
	{
	public:
		// 创建一个空的画板，基于当前 FBO
		static Drawable* createShared();
		// width, height 不是偶数，会导致blit少一行，所以会自动转成偶数。
		// 注意：如果 samples 大于 0，bitmap 将不可用。
		static Drawable* create(int width, int height, int samples);

		int width() const;
		int height() const;
		int samples() const;

		void begin();
		void clear();
		void clear(float r, float g, float b, float a=1);
		void clearColor(float r, float g, float b, float a=1);
		void clearDepth();
		
		void blit(GLuint dstFbo);
		void blit(Drawable *buffer=NULL);

		void flush();
		void finish();
		
		// 调用者不可释放此对象
		Bitmap* bitmap();

		~Drawable();
		
	private:
		Drawable();
		Drawable(const Drawable &d);
		Drawable& operator =(const Drawable &d);

		void width(int width);
		void height(int height);
		void samples(int samples);
		
		void setupFBO();

		int _width;
		int _height;
		int _samples;
		
		bool _isShared;
		GLuint _framebuffer;
		GLuint _colorbuffer;
		GLuint _depthbuffer;

		Bitmap *_bitmap;
	};
}; // end namespace

#endif /* Drawable_hpp */
