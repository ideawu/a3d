//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include "Node.h"

namespace a3d{
	typedef enum{
		AnimateStateNone,
		AnimateStateBegin,
		AnimateStateWillUpdate,
		AnimateStateDidUpdate,
		AnimateStateEnd
	}AnimateState;
	
	class Animate
	{
	public:
		Animate();
		Animate(const Animate &a);
		~Animate();
		
		AnimateState state() const;
		
		void updateAtTime(float time);
		// 子类方法
		virtual void update(float progress) = 0;
	private:
		AnimateState _state;
		Node *_target;
		float _beginTime;
		float _duration;
		float _currentTime;
		
		void updateState(AnimateState state);
	};
}; // end namespace

#endif /* Animation_hpp */
