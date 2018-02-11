//  Created by ideawu on 18-2-11.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#ifndef __a3d__AnimateSize__
#define __a3d__AnimateSize__

#include "Animate.h"

namespace a3d{
	class AnimateSize : public Animate
	{
	public:
		static AnimateSize* size(const Vector3 &size);

		virtual void update(double progress, Node *target, const Node *origin);

	private:
		Vector3 _size;
	};
}; // end namespace

#endif /* defined(__a3d__AnimateSize__) */
