//  Created by ideawu on 18-2-10.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#ifndef __a3d__Quaternion__
#define __a3d__Quaternion__

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

		Quaternion invert() const;

		GLKQuaternion _quat;
	private:

		Quaternion(const GLKQuaternion &q);
	};
}; // end namespace

#endif /* defined(__a3d__Quaternion__) */
