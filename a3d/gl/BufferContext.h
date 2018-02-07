//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_BufferContext_hpp
#define a3d_BufferContext_hpp

#include "Context.h"

namespace a3d{
	// FBO
	// TextureBuffer/TextureFBO: render to texture
	// ColorBuffer/ColorFBO: render to color storage
	
 	class BufferContext : public Context
	{
	public:
		BufferContext();
		~BufferContext();
		
		virtual GLuint framebuffer();
		virtual void setup();

	private:
		GLuint _framebuffer;
		GLuint _colorbuffer;
		GLuint _depthbuffer;
	};
}; // end namespace

#endif /* BufferContext_hpp */
