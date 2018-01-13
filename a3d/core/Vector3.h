//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Vector3_hpp
#define Vector3_hpp

#include <GLKit/GLKMath.h>

namespace a3d{
	class Vector3
	{
	private:
		GLKVector3 _vec;
		Vector3(GLKVector3 vec);
		
	public:
		static Vector3 zero();

		Vector3();
		Vector3(const Vector3 &vec);
		Vector3(float x, float y, float z);
		
	public:
		float x() const;
		float y() const;
		float z() const;
		float length() const;

	public:
		Vector3 normalize() const;
		Vector3 normalize(float norm) const;

		Vector3 negate() const;
		// alias of negate
		Vector3 invert() const;
		
		Vector3 add(Vector3 vec) const;
		Vector3 sub(Vector3 vec) const;
		float dot(Vector3 vec) const;
		Vector3 cross(Vector3 vec) const;
		Vector3 project(Vector3 vec) const;
	};
	
}; // end namespace

#endif /* Vector3_hpp */
