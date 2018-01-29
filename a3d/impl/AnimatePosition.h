//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef AnimatePosition_hpp
#define AnimatePosition_hpp

#include "Animate.h"
#include "Node.h"
#include "Vector3.h"

namespace a3d{
	class AnimatePosition : public Animate
	{
	public:
		static AnimatePosition* move(const Vector3 &vec);
		static AnimatePosition* moveTo(const Vector3 &pos);

		virtual void update(double progress, Node *target, const Node *origin);
	private:
		Vector3 _vec;
		
		typedef enum{
			MoveTypeOffset,
			MoveTypePosition
		}MoveType;
		
		MoveType _type;
	};
}; // end namespace

#endif /* AnimatePosition_hpp */
