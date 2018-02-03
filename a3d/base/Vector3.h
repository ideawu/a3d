//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Vector3_hpp
#define Vector3_hpp

#include <string>

namespace a3d{
	class Vector3
	{
	public:
		union{
			struct{float x, y, z;};
			struct{float w, h, d;};
			struct{float width, height, depth;};
			float m[3];
		};
		
		static Vector3 slerp(const Vector3 &origin, const Vector3 &target, float progress);

		Vector3();
		Vector3(float x, float y, float z);
		std::string str() const;

	public:
		bool empty() const;
		float length() const;

		Vector3 normalize() const;
		Vector3 normalize(float norm) const;

		Vector3 negate() const;
		// alias of negate
		Vector3 invert() const;
		
		Vector3 add(const Vector3 &vec) const;
		Vector3 sub(const Vector3 &vec) const;
		Vector3 mul(float scalar) const;
		float dot(const Vector3 &vec) const;
		Vector3 cross(const Vector3 &vec) const;
		Vector3 project(const Vector3 &vec) const;
	};
	
}; // end namespace

#endif /* Vector3_hpp */
