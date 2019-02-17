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
		// 基于当前已存在的 CGLContextObj
		static GLContext* createShared();
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
		bool _isShared;
	};
}; // end namespace

#endif /* GLContext_hpp */
