//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include "Camera.h"

namespace a3d{
	void init();
	void free();
	
	void setupCamera(float width, float height, float depth);
	void setupCamera(float fovy, float width, float height, float depth);
	
	class Engine
	{
	public:
		Engine();
		~Engine();
		
		Camera *camera;
	};
	
}; // end namespace

#endif /* Engine_hpp */
