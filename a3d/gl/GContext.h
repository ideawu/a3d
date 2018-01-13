//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef GLContext_hpp
#define GLContext_hpp

#include <OpenGL/gl.h>
#include "Matrix4.h"

namespace a3d{
	class GContext
	{
	public:
		// 如果 width, height 不是偶数，会导致blit少一行，所以转成偶数。
		static GContext* memoryContext(float width, float height);

	public:
		float width() const;
		float height() const;

		void bind3D(const Matrix4 &mat);
		void bind2D(const Matrix4 &mat);
		// 将渲染结果复制到默认缓冲
		void flush();

	protected:
		GContext(){}

		virtual GLuint framebuffer(){return 0;};
		virtual void setup() = 0;
	private:
		GContext(const GContext &ctx){}
		void width(float width);
		void height(float height);

		float _width;
		float _height;
	};
	
}; // end namespace

#endif /* GLContext_hpp */
