//  Created by ideawu on 2019/2/10.
//  Copyright © 2019 ideawu. All rights reserved.
//

#ifndef GLContext_hpp
#define GLContext_hpp

#include "Renderer.h"

namespace a3d{
	// Each thread has a single current OpenGL rendering context
	class GLContext
	{
	public:
		static GLContext* create();
		static GLContext* current();

		~GLContext();
		
		Renderer* renderer() const;

		void makeCurrent();
		
	private:
		GLContext();
		GLContext(const GLContext &d);
		GLContext& operator =(const GLContext &d);

		Renderer *_renderer;
		CGLContextObj _CGLContext;
	};
}; // end namespace

#endif /* GLContext_hpp */
