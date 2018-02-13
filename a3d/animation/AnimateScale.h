//  Created by ideawu on 18-2-11.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#ifndef __a3d__AnimateScale__
#define __a3d__AnimateScale__

#include "Animate.h"

namespace a3d{
	class AnimateScale : public Animate
	{
	public:
		static AnimateScale* scale(const Vector3 &s);

		virtual void update(double progress, Node *target);
	private:
		Vector3 _scale;
	};
}; // end namespace

#endif /* defined(__a3d__AnimateScale__) */
