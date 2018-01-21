//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include "AnimationTypes.h"

namespace a3d{
	class Node;
	
	class Animate
	{
	public:
//		static Animate* move(Vector3 offset);
//		static Animate* moveTo(Vector3 pos);

	public:
		virtual ~Animate();

		// 子类方法
		virtual void update(float progress, Node *current, const Node *origin){}

		AnimateState state() const;
		void state(AnimateState state);
		float duration() const;
		void duration(float duration);
		void timingFunc(AnimateTimingFunc func);

		// 框架方法，根据 origin 更新 current
		void updateAtTime(float time, Node *current, const Node *origin);

	protected:
		Animate();
	private:
		Animate(const Animate &a);
		Animate& operator =(const Animate& d);

		AnimateState _state;
		AnimateTimingFunc _timingFunc;
		// 指定 timingOffset 时，动画时间不是从0到1，而是从offset到offset+1
		float _timingOffset;
		AnimateCallback _callback;
		void *_callbackCtx;
		
		float _beginTime;
		float _currentTime;
		float _duration;
		
	};
}; // end namespace

#endif /* Animation_hpp */
