//  Created by ideawu on 2019/2/10.
//  Copyright © 2019 ideawu. All rights reserved.
//

#ifndef GLContext_hpp
#define GLContext_hpp

namespace a3d{
	class GLContext
	{
	public:
		static GLContext* create();

		void makeCurrent();
		~GLContext();

	private:
		GLContext();
		GLContext(const GLContext &d);
		GLContext& operator =(const GLContext &d);

		CGLContextObj _CGLContext;
	};
}; // end namespace

#endif /* GLContext_hpp */
