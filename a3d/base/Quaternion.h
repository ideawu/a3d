//  Created by ideawu on 18-2-10.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#ifndef a3d_Quaternion_
#define a3d_Quaternion_

#include <GLKit/GLKMath.h>
#include "Vector3.h"

namespace a3d{
	class Quaternion
	{
	public:
		static Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float progress);

		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(float angle, const Vector3 &vec);

		float angle() const;
		Vector3 vector() const;

		float x() const;
		float y() const;
		float z() const;
		float w() const;

		Quaternion add(const Quaternion &q) const;
		Quaternion sub(const Quaternion &q) const;
		Quaternion mul(const Quaternion &q) const;
		Quaternion div(const Quaternion &q) const;
		Quaternion invert() const;

	private:
		GLKQuaternion _quat;

		Quaternion(const GLKQuaternion &q);
	};
}; // end namespace

#endif /* defined(__a3d__Quaternion__) */
