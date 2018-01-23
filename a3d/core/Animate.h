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
		
		// 设置弹跳次数，默认是1次，如果指定2次，动画完毕后返回原点，可指定非整数次
		void bounce(float count);
		
		// 运动位移相对时间的曲线控制
		void easingFunc(AnimateTimingFunc func);
		// 用于弹跳频率控制
		void bounceFunc(AnimateTimingFunc func);
		// 用于弹跳力度控制
		void accelateFunc(AnimateTimingFunc func);

		// 框架方法，根据 origin 更新 current
		void updateAtTime(float time, Node *current, const Node *origin);

	protected:
		Animate();
	private:
		Animate(const Animate &a);
		Animate& operator =(const Animate& d);

		AnimateState _state;
		float _bounce;
		AnimateTimingFunc _easingFunc;
		AnimateTimingFunc _bounceFunc;
		AnimateTimingFunc _accelateFunc;

		AnimateCallback _callback;
		void *_callbackCtx;
		
		float _beginTime;
		float _duration;
		
		float timing(float p) const;
	};
}; // end namespace

#endif /* Animation_hpp */
