//  Created by ideawu on 2019/2/10.
//  Copyright © 2019 ideawu. All rights reserved.
//

#ifndef Context_hpp
#define Context_hpp

#include "Renderer.h"

namespace a3d{
	// Each thread has a single current OpenGL rendering context
	class Context
	{
	public:
		// 基于当前已存在的 CContextObj
		static Context* createShared();
		static Context* create();
		static Context* current();

		~Context();
		
		Renderer* renderer() const;

		void makeCurrent();
		
	private:
		Context();
		Context(const Context &d);
		Context& operator =(const Context &d);

		Renderer *_renderer;
		CGLContextObj _CGLContext;
		bool _isShared;
	};
}; // end namespace

#endif /* Context_hpp */
