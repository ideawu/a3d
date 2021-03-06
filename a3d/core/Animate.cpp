//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Animate.h"
#include "AnimatePosition.h"
#include "AnimateRotation.h"
#include "AnimateScale.h"
#include "AnimateOpacity.h"
#include "AnimateSize.h"

static const double AUTO_BEGIN_TIME = 999999999.0;

namespace a3d{
	Animate* Animate::move(float x, float y, float z, double duration){
		return AnimatePosition::move(Vector3(x, y, z), duration);
	}

	Animate* Animate::move(const Vector3 &vec, double duration){
		return AnimatePosition::move(vec, duration);
	}

	Animate* Animate::position(float x, float y, float z, double duration){
		return AnimatePosition::position(Vector3(x, y, z), duration);
	}

	Animate* Animate::position(const Vector3 &pos, double duration){
		return AnimatePosition::position(pos, duration);
	}

	Animate* Animate::rotate(float degree, const Vector3 &vec){
		return AnimateRotation::rotate(degree, vec);
	}
	
	Animate* Animate::rotate(float degree, const Axis &axis){
		return AnimateRotation::rotate(degree, axis);
	}

	Animate* Animate::rotation(const Quaternion &quat){
		return AnimateRotation::rotation(quat);
	}

	Animate* Animate::scale(float xyz){
		return AnimateScale::scale(Vector3(xyz, xyz, xyz));
	}

	Animate* Animate::scale(float x, float y, float z){
		return AnimateScale::scale(Vector3(x, y, z));
	}

	Animate* Animate::scale(const Vector3 &s){
		return AnimateScale::scale(s);
	}

	Animate* Animate::scaleTo(const Vector3 &s){
		return AnimateScale::scaleTo(s);
	}

	Animate* Animate::opacity(double opacity, double duration){
		return AnimateOpacity::opacity(opacity, duration);
	}

	Animate* Animate::show(double duration){
		return Animate::opacity(1, duration);
	}

	Animate* Animate::hide(double duration){
		return Animate::opacity(0, duration);
	}

	Animate* Animate::size(float w, float h, float d){
		return AnimateSize::size(Vector3(w, h, d));
	}

	Animate* Animate::size(const Vector3 &size){
		return AnimateSize::size(size);
	}


	Animate::Animate(){
		_state = AnimateStateNone;
		_easingFunc = TimingFuncEaseOut;
		_bounceFunc = TimingFuncLinear;
		_accelateFunc = TimingFuncNone;
		_callback = NULL;
		_beginTime = AUTO_BEGIN_TIME;
		_duration = 0;
		_bounce = 0;
		_repeats = 0;
		_disposable = true;
	}
	
	Animate::~Animate(){
	}

	AnimateState Animate::state() const{
		return _state;
	}

	void Animate::state(AnimateState state){
		_state = state;
		if(_callback){
			_callback(*this, _callbackCtx);
		}
	}

	bool Animate::isEnded() const{
		return _state == AnimateStateEnded;
	}

	double Animate::beginTime() const{
		return _beginTime;
	}
	
	void Animate::beginTime(double beginTime){
		_beginTime = beginTime;
	}

	double Animate::duration() const{
		return _duration;
	}
	
	void Animate::duration(double duration){
		_duration = duration;
	}

	void Animate::callback(AnimateCallback func, void *ctx){
		_callback = func;
		_callbackCtx = ctx;
	}
	
	int Animate::bounce() const{
		return _bounce;
	}

	void Animate::bounce(int count){
		_bounce = count;
	}

	int Animate::repeats() const{
		return _repeats;
	}

	void Animate::repeats(int count){
		_repeats = count;
	}

	void Animate::loop(bool enable){
		_repeats = enable? -1 : 0;
	}

	bool Animate::disposable() const{
		return _disposable;
	}

	void Animate::disposable(bool enable){
		_disposable = enable;
	}

	void Animate::timingFunc(TimingFunc func){
		easingFunc(func);
	}

	void Animate::easingFunc(TimingFunc func){
		_easingFunc = func;
	}
	
	void Animate::bounceFunc(TimingFunc func){
		_bounceFunc = func;
	}
	
	void Animate::accelateFunc(TimingFunc func){
		_accelateFunc = func;
	}
	
	static double reverse_timing_func(TimingFunc func, double val){
		double s = 0;
		double e = 1.0;
		double t = (e-s)/2;
		double epsilon = 0.00001;
		while(1){
			double v = func(t);
			if(fabs(v-val) < epsilon || fabs(t-e) < epsilon || fabs(t-s) < epsilon){
				return t;
			}
			if(v > val){
				e = t;
			}else{
				s = t;
			}
			t = s + (e-s)/2;
		}
	}

	double Animate::timing(double p) const{
		double step_s = 0;
		double step_e = 0;
		if(_bounce != 0){
			// 通过反函数计算当前时间是第几跳
			double curr_bounce = reverse_timing_func(_bounceFunc, p);
			// 相邻的两次组成一次周期
			step_s = floor(curr_bounce * (_bounce + 1)/2.0) * 2;
			step_e = step_s+2;
			// 周期的开始和结束时间
			double time_s = _bounceFunc(step_s/(_bounce + 1));
			double time_e = _bounceFunc(step_e/(_bounce + 1));
//			log_debug("curr: %.3f, s: %.3f, e: %.3f, ts: %.3f, te: %.3f", curr_bounce, step_s, step_e, time_s, time_e);
			// 将周期内对称的两条线归一化(*2)
			p = (p - time_s)/(time_e - time_s);
			p = (p < 0.5)? 2 * p : 2 * (1-p);
		}
		
		double y = _easingFunc(p);
		
		if(_bounce != 0){
			double total_steps = ceil((_bounce + 1)/2.0) * 2; // 向上取偶
			y *= _accelateFunc(step_e/total_steps);
		}
		return y;
	}

	void Animate::updateAtTime(double time, Node *target){
		// auto start
		if(_beginTime == AUTO_BEGIN_TIME){
			_beginTime = time;
		}
		// ignore before begin time
		if(time < _beginTime){
			return;
		}
		
		if(_state == AnimateStateNone){
			this->state(AnimateStateBegan);
		}

		double progress;
		progress = (time - _beginTime)/_duration;
		progress = fmin(1, progress);
		progress = fmax(0, progress);
		
		this->state(AnimateStateWillUpdate);
		{
			double timing_p = this->timing(progress);
			update(timing_p, target);
		}
		this->state(AnimateStateDidUpdate);

		if(progress >= 1){
			this->state(AnimateStateEnded);
			if(!this->disposable()){
				this->state(AnimateStateNone);
			}
			if(_repeats != 0){
				if(_repeats > 0){
					_repeats --;
				}
				_beginTime = AUTO_BEGIN_TIME;
				this->state(AnimateStateNone);
			}
		}
	}

}; // end namespace
