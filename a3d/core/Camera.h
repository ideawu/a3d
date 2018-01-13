//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Object.h"

namespace a3d{
	class Camera : public Object
	{
	private:
		float _fovy;
		float _near;
		float _far;
		Matrix4 _matrix3d;
		Matrix4 _matrix2d;

		Camera(const Camera &cam){}
		void set(float fovy, float width, float height, float depth);
		
	public:
		Camera(float fovy, float width, float height, float depth);
		
	public:
		void setup();
		void setup(float width, float height);
		void setup(float width, float height, float depth);
		void setup(float fovy, float width, float height, float depth);
	};
	
}; // end namespace

#endif /* Camera_hpp */
