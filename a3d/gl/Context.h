//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef GLContext_hpp
#define GLContext_hpp

#include "Matrix4.h"

namespace a3d{
	class Context
	{
	public:
		// 使用当前的OpenGL上下文
		static Context* shared();
		// 创建一个FBO，如果 width, height 不是偶数，会导致blit少一行，所以转成偶数。
		static Context* bufferContext(float width, float height);

	public:
		virtual ~Context(){};

		float width() const;
		float height() const;
		
		void loadMatrix3D(const Matrix4 &mat);
		void loadMatrix2D(const Matrix4 &mat);

		void bind();
		void clear();
		void clear(float r, float g, float b, float a=1);
		void flush();
		void finish();
		// TODO: blit other FBO
		void blit();

	protected:
		Context();

		virtual GLuint framebuffer() = 0;
		virtual void setup() = 0;
	private:
		Context(const Context &d);
		Context& operator =(const Context& d);

		void width(float width);
		void height(float height);

		float _width;
		float _height;
	};
	
}; // end namespace

#endif /* GLContext_hpp */
