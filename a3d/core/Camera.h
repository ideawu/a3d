//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Camera_hpp
#define a3d_Camera_hpp

#include "Node.h"

namespace a3d{

	class Camera : public Node
	{
	public:
		Camera(){}

		static Camera* create();
		// in points, not in pixels
		static Camera* create(float fovy, float width, float height, float depth, float eyeZ=0);
		
		// in points, not in pixels
		void setup(float fovy, float width, float height, float depth, float eyeZ=0);
		
		Matrix4 matrix3D() const;
		Matrix4 matrix2D() const;

	private:
		Camera(const Camera &d);
		Camera& operator =(const Camera &d);

		float _fovy;
		float _aspect;
		float _near;
		float _far;

		Matrix4 _matrix3D;
		Matrix4 _matrix2D;
	};
	
}; // end namespace

#endif /* Camera_hpp */
