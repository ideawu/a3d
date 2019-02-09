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
		static Animate* position(float x, float y, float z, double duration=0);
		static Animate* position(const Vector3 &pos, double duration=0);

		static Animate* rotate(float degree, const Vector3 &vec);
		static Animate* rotate(float degree, const Axis &axis);
		static Animate* rotation(const Quaternion &quat);

		static Animate* scale(float xyz);
		static Animate* scale(float x, float y, float z);
		static Animate* scale(const Vector3 &s);
		static Animate* scaleTo(const Vector3 &s);

		static Animate* opacity(double opacity, double duration=0);
		static Animate* show(double duration=0);
		static Animate* hide(double duration=0);

		static Animate* size(float w, float h, float d);
		static Animate* size(const Vector3 &size);

	public:
		virtual ~Animate();

		// 子类方法，注意，TimingFunc可能使progress大于1或小于0
		virtual void update(double progress, Node *target) = 0;

		AnimateState state() const;
		void state(AnimateState state);
		bool isEnded() const;

		double beginTime() const;
		// 动画开始的时间点，-1表示下一次执行时开始
		void beginTime(double beginTime);
		double duration() const;
		void duration(double duration);
		
		int repeats() const;
		// <0: forever; 0: don't repeat(default);
		void repeats(int count);
		void loop(bool enable);
		int bounce() const;
		// 设置弹跳次数(在 duration 时间内)，如果指定奇数次，动画完毕后返回原点
		void bounce(int count);
		// 是否在动画执行完毕后释放，默认是
		bool disposable() const;

		void callback(AnimateCallback func, void *ctx);

		// 运动位移相对时间的曲线控制
		void timingFunc(TimingFunc func); // alias of easingFunc
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
		
		double _beginTime;
		double _duration;
		int _repeats;
		int _bounce;
		bool _disposable;
		
		double timing(double p) const;
	};
}; // end namespace

#endif /* Animation_hpp */
