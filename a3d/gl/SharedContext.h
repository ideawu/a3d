//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef SharedContext_hpp
#define SharedContext_hpp

#include "Context.h"

namespace a3d{
	class SharedContext : public Context
	{
	public:
		SharedContext(){}
		~SharedContext(){}
		
		virtual GLuint framebuffer(){return 0;}
		virtual void setup(){}
	};
}; // end namespace

#endif /* SharedContext_hpp */
