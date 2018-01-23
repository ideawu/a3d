//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Animate.h"

namespace a3d{
	Animate::Animate(){
		_state = AnimateStateNone;
		_easingFunc = AnimateTimingEaseOut;
		_bounceFunc = AnimateTimingLinear;
		_accelateFunc = AnimateTimingNone;
		_callback = NULL;
		_beginTime = -1;
		_duration = 0;
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

	float Animate::duration() const{
		return _duration;
	}
	
	void Animate::duration(float duration){
		_duration = duration;
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
	
	static float reverse_timing_func(AnimateTimingFunc func, float val){
		float s = 0;
		float e = 1.0;
		float t = (e-s)/2;
		float epsilon = 0.00001;
		while(1){
			float v = func(t);
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

	float Animate::timing(float p) const{
		float step_s = 0;
		float step_e = 0;
		if(_bounce != 0){
			// 通过反函数计算当前时间是第几跳
			float bounce_ratio = reverse_timing_func(_bounceFunc, p);
			// 相邻的两次组成一次周期
			step_s = floor(bounce_ratio * _bounce/2) * 2; // 向下取偶
			step_e = step_s+2;
			// 周期的开始和结束时间
			float time_s = _bounceFunc(step_s/_bounce);
			float time_e = _bounceFunc(step_e/_bounce);
			
			p = (p - time_s)/(time_e - time_s);
			p = (p < 0.5)? 2 * p : 2 * (1-p);
		}
		
		float y = _easingFunc(p);
		
		if(_bounce != 0){
			float total_steps = ceil(_bounce/2) * 2; // 向上取偶
			y *= _accelateFunc(step_e/total_steps);
		}
		return y;
	}

	void Animate::updateAtTime(float time, Node *current, const Node *origin){
		if(_state == AnimateStateNone){
			_beginTime = time;
			this->state(AnimateStateBegin);
		}
		
		if(_state != AnimateStateNone && _state != AnimateStateEnd){
			float progress;
			float timing_p;
			if(time < _beginTime){
				progress = 1;
				timing_p = 1;
			}else if(_duration == 0){
				return;
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
