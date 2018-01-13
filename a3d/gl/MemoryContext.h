//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef MemoryContext_hpp
#define MemoryContext_hpp

#include "Context.h"

namespace a3d{
	class MemoryContext : public Context
	{
	public:
		MemoryContext();
		~MemoryContext();
		
		virtual GLuint framebuffer();
		virtual void setup();

	private:
		GLuint _framebuffer;
		GLuint _colorbuffer;
		GLuint _depthbuffer;
	};
}; // end namespace

#endif /* MemoryContext_hpp */
