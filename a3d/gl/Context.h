//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Context_hpp
#define a3d_Context_hpp

#include "Matrix4.h"

namespace a3d{
	class Renderer;
	
	class Context
	{
	public:
		static Context* current();
		static Context* blankContext();
		// 创建一个FBO，如果 width, height 不是偶数，会导致blit少一行，所以转成偶数。
		static Context* bufferContext(int width, int height);

	public:
		virtual ~Context();
		
		Renderer* renderer() const;

		int width() const;
		int height() const;
		
		void loadMatrix3D(const Matrix4 &mat);
		void loadMatrix2D(const Matrix4 &mat);

		void begin();
		void clear();
		void clear(float r, float g, float b, float a=1);
		void clearColor(float r, float g, float b, float a=1);
		void clearDepth();
		void flush();
		void finish();
		// TODO: blit to other FBO
		void blit();

	protected:
		Context();

		virtual GLuint framebuffer() = 0;
		virtual void setup() = 0;
	private:
		Context(const Context &d);
		Context& operator =(const Context &d);

		void loadMatrix(const Matrix4 &mat);

		void width(int width);
		void height(int height);

		int _width;
		int _height;
		
		Renderer *_renderer;
	};
}; // end namespace

#endif /* GLContext_hpp */
