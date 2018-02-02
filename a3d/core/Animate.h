//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include "AnimationTypes.h"
#include "Node.h"
#include "Vector3.h"
#include "Axis.h"

namespace a3d{
	class Node;
	
	class Animate
	{
	public:
		static Animate* move(const Vector3 &vec, double duration);
		static Animate* moveTo(const Vector3 &pos, double duration);
		
		static Animate* fadeTo(double opacity, double duration);
		static Animate* show(double duration);
		static Animate* hide(double duration);

		static Animate* rotate(float degree, const Vector3 &vec);
		static Animate* rotate(float degree, const Axis &axis);

	public:
		virtual ~Animate();

		// 子类方法
		virtual void update(double progress, Node *target, const Node *origin) = 0;

		AnimateState state() const;
		void state(AnimateState state);
		double duration() const;
		void duration(double duration);
		
		void callback(AnimateCallback func, void *ctx);
		
		// 设置弹跳次数，默认是1次，如果指定2次，动画完毕后返回原点，可指定非整数次
		// bounce 是偶数且 boundFunc 为 Linear(默认)，则作用同 repeat+autoreverse
		float bounce() const;
		void bounce(float count);
		
		// 运动位移相对时间的曲线控制
		void easingFunc(AnimateTimingFunc func);
		// 用于弹跳频率控制
		void bounceFunc(AnimateTimingFunc func);
		// 用于弹跳力度控制
		void accelateFunc(AnimateTimingFunc func);

		// 框架方法，根据 origin 更新 current
		void updateAtTime(double time, Node *current, const Node *origin);

	protected:
		Animate();
	
	private:
		Animate(const Animate &a);
		Animate& operator =(const Animate &d);

		AnimateState _state;
		AnimateTimingFunc _easingFunc;
		AnimateTimingFunc _bounceFunc;
		AnimateTimingFunc _accelateFunc;

		AnimateCallback _callback;
		void *_callbackCtx;
		
		float _bounce;
		double _beginTime;
		double _duration;
		
		double timing(double p) const;
	};
}; // end namespace

#endif /* Animation_hpp */
