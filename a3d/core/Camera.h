//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Object.h"

namespace a3d{
	class Camera : public Object
	{
	public:
		static Camera* create(float fovy, float width, float height, float depth);

	public:
		Matrix4 matrix3D() const;
		Matrix4 matrix2D() const;

	private:
		float _fovy;
		float _near;
		float _far;
		Matrix4 _matrix3D;
		Matrix4 _matrix2D;
		
		Camera(){}
		Camera(const Camera &cam){}
		void setup(float fovy, float width, float height, float depth);
	};
	
}; // end namespace

#endif /* Camera_hpp */
