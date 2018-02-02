//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Animate.h"
#include "AnimateOpacity.h"
#include "AnimatePosition.h"
#include "AnimateRotation.h"

namespace a3d{
	
	Animate* Animate::move(const Vector3 &vec, double duration){
		Animate *ret = AnimatePosition::move(vec);
		ret->duration(duration);
		return ret;
	}
	
	Animate* Animate::moveTo(const Vector3 &pos, double duration){
		Animate *ret = AnimatePosition::moveTo(pos);
		ret->duration(duration);
		return ret;
	}
	
	Animate* Animate::fadeTo(double opacity, double duration){
		Animate *ret = AnimateOpacity::fadeTo(opacity);
		ret->duration(duration);
		return ret;
	}

	Animate* Animate::show(double duration){
		return Animate::fadeTo(1, duration);
	}
	
	Animate* Animate::hide(double duration){
		return Animate::fadeTo(0, duration);
	}
	
	Animate* Animate::rotate(float degree, const Vector3 &vec){
		Animate *ret = AnimateRotation::rotate(degree, vec);
		return ret;
	}
	
	Animate* Animate::rotate(float degree, const Axis &axis){
		Animate *ret = AnimateRotation::rotate(degree, axis);
		return ret;
	}

	Animate::Animate(){
		_state = AnimateStateNone;
		_easingFunc = AnimateTimingEaseOut;
		_bounceFunc = AnimateTimingLinear;
		_accelateFunc = AnimateTimingNone;
		_callback = NULL;
		_beginTime = -1;
		_duration = 0;
		_bounce = 1;
	}
	
	Animate::~Animate(){
	}

	AnimateState Animate::state() const{
		return _state;
	}

	void Animate::state(AnimateState state){
		_state = state;
		if(_callback){
			_callback(this, _callbackCtx);
		}
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
	
	float Animate::bounce() const{
		return _bounce;
	}

	void Animate::bounce(float count){
		_bounce = count;
	}
	
	void Animate::easingFunc(AnimateTimingFunc func){
		_easingFunc = func;
	}
	
	void Animate::bounceFunc(AnimateTimingFunc func){
		_bounceFunc = func;
	}
	
	void Animate::accelateFunc(AnimateTimingFunc func){
		_accelateFunc = func;
	}
	
	static double reverse_timing_func(AnimateTimingFunc func, double val){
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
		if(_bounce != 1){
			// 通过反函数计算当前时间是第几跳
			double bounce_ratio = reverse_timing_func(_bounceFunc, p);
			// 相邻的两次组成一次周期
			step_s = floor(bounce_ratio * _bounce/2) * 2; // 向下取偶
			step_e = step_s+2;
			// 周期的开始和结束时间
			double time_s = _bounceFunc(step_s/_bounce);
			double time_e = _bounceFunc(step_e/_bounce);
			
			p = (p - time_s)/(time_e - time_s);
			p = (p < 0.5)? 2 * p : 2 * (1-p);
		}
		
		double y = _easingFunc(p);
		
		if(_bounce != 1){
			double total_steps = ceil(_bounce/2) * 2; // 向上取偶
			y *= _accelateFunc(step_e/total_steps);
		}
		return y;
	}

	void Animate::updateAtTime(double time, Node *current, const Node *origin){
		if(_state == AnimateStateNone){
			_beginTime = time;
			this->state(AnimateStateBegin);
		}
		
		if(_state != AnimateStateNone && _state != AnimateStateEnd){
			double progress;
			double timing_p;
			if(time < _beginTime){
				return;
			}else if(_duration == 0){
				progress = 1;
				timing_p = 1;
			}else{
				progress = (time - _beginTime)/_duration;
				progress = fmin(1, progress);
				timing_p = this->timing(progress);
			}

			this->state(AnimateStateWillUpdate);
			update(timing_p, current, origin);
			this->state(AnimateStateDidUpdate);

			if(progress >= 1){
				this->state(AnimateStateEnd);
			}
		}
	}

}; // end namespace
