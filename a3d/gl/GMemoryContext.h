//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef GMemoryContext_hpp
#define GMemoryContext_hpp

#include "GContext.h"

namespace a3d{
	class GMemoryContext : public GContext
	{
	public:
		GMemoryContext();
		~GMemoryContext();
		
		virtual GLuint framebuffer();
		virtual void setup();

	private:
		GLuint _framebuffer;
		GLuint _colorbuffer;
		GLuint _depthbuffer;
	};
}; // end namespace

#endif /* GMemoryContext_hpp */
