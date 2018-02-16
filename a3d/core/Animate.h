//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Animation_hpp
#define a3d_Animation_hpp

#include "AnimationTypes.h"
#include "Node.h"

namespace a3d{
	class Animate
	{
	public:
		static Animate* move(float x, float y, float z, double duration=0);
		static Animate* move(const Vector3 &vec, double duration=0);
		static Animate* moveTo(float x, float y, float z, double duration=0);
		static Animate* moveTo(const Vector3 &pos, double duration=0);

		static Animate* rotate(float degree, const Vector3 &vec);
		static Animate* rotate(float degree, const Axis &axis);
		static Animate* rotateTo(const Quaternion &quat);

		static Animate* scale(float xyz);
		static Animate* scale(float x, float y, float z);
		static Animate* scale(const Vector3 &s);

		static Animate* fadeTo(double opacity, double duration=0);
		static Animate* show(double duration=0);
		static Animate* hide(double duration=0);

		static Animate* size(float w, float h, float d);
		static Animate* size(const Vector3 &size);

	public:
		virtual ~Animate();

		// 子类方法，注意，TimingFunc可能使progress大于1或小于0，但结束时progress必为1
		virtual void update(double progress, Node *target) = 0;

		AnimateState state() const;
		void state(AnimateState state);
		bool isEnded() const;

		double duration() const;
		void duration(double duration);
		double beginTime() const;
		void beginTime(double beginTime);
		int repeats() const;
		void repeats(int count);
		void repeat(bool enable);
		// 设置弹跳次数，默认是1次，如果指定2次，动画完毕后返回原点，可指定非整数次
		// bounce 是偶数且 boundFunc 为 Linear(默认)，则作用同 repeat+autoreverse
		float bounces() const;
		void bounces(float count);

		void callback(AnimateCallback func, void *ctx);

		// 运动位移相对时间的曲线控制
		void easingFunc(TimingFunc func);
		// 用于弹跳频率控制
		void bounceFunc(TimingFunc func);
		// 用于弹跳力度控制
		void accelateFunc(TimingFunc func);

		// 框架方法
		void updateAtTime(double time, Node *target);

	protected:
		Animate();

	private:
		Animate(const Animate &a);
		Animate& operator =(const Animate &d);

		AnimateState _state;
		TimingFunc _easingFunc;
		TimingFunc _bounceFunc;
		TimingFunc _accelateFunc;

		AnimateCallback _callback;
		void *_callbackCtx;
		
		int _repeats;
		float _bounces;
		double _beginTime;
		double _duration;
		
		double timing(double p) const;
	};
}; // end namespace

#endif /* Animation_hpp */
