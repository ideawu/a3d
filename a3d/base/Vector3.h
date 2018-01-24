//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Vector3_hpp
#define Vector3_hpp

namespace a3d{
	class Vector3
	{
	public:
		union{
			float x;
			float w;
			float width;
		};
		union{
			float y;
			float h;
			float height;
		};
		union{
			float z;
			float d;
			float depth;
		};

		Vector3();
		Vector3(float x, float y, float z);
		
	public:
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
