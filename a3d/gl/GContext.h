//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef GLContext_hpp
#define GLContext_hpp

#include <OpenGL/gl.h>
#include "Camera.h"

namespace a3d{
	class GContext
	{
	public:
		// 如果 width, height 不是偶数，会导致blit少一行，所以转成偶数。
		static GContext* memoryContext(float width, float height);

	public:
		virtual ~GContext(){};

		float width() const;
		float height() const;

		void bind();
		void clear();
		void clear(float r, float g, float b, float a=1);
		void setupCamera3D(const Camera *camera);
		void setupCamera2D(const Camera *camera);
		void finish();

	protected:
		GContext(){}

		virtual GLuint framebuffer() = 0;
		virtual void setup() = 0;
	private:
		GContext(const GContext &ctx){}
		void width(float width);
		void height(float height);
		void loadMatrix(const Matrix4 &mat);

		float _width;
		float _height;
	};
	
}; // end namespace

#endif /* GLContext_hpp */