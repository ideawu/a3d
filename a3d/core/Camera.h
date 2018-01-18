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
		Camera(){}
		
		// in points, not in pixels
		static Camera* create(float fovy, float width, float height, float depth);

		Matrix4 matrix3D() const;
		Matrix4 matrix2D() const;
		
		// in points, not in pixels
		void setup(float fovy, float width, float height, float depth);

	private:
		float _fovy;
		float _near;
		float _far;
		Matrix4 _matrix3D;
		Matrix4 _matrix2D;
		
		Camera(const Camera &d);
		Camera& operator =(const Camera& d);
	};
	
}; // end namespace

#endif /* Camera_hpp */
