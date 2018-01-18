//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef AnimatePosition_hpp
#define AnimatePosition_hpp

#include "Animate.h"
#include "Vector3.h"

namespace a3d{
	class AnimatePosition : public Animate
	{
	public:
		static AnimatePosition* move(Vector3 offset);
		static AnimatePosition* moveTo(Vector3 pos);

		virtual void update(float progress, Node *current, const Node *origin);
	private:
		Vector3 _vec;
		
		typedef enum{
			MoveTypeOffset,
			MoveTypeDestination
		}MoveType;
		
		MoveType _type;
	};
}; // end namespace

#endif /* AnimatePosition_hpp */
