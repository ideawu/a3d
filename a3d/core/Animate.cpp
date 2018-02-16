//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Animate.h"
#include "AnimatePosition.h"
#include "AnimateRotation.h"
#include "AnimateScale.h"
#include "AnimateOpacity.h"
#include "AnimateSize.h"

namespace a3d{
	
	Animate* Animate::move(float x, float y, float z, double duration){
		return AnimatePosition::move(Vector3(x, y, z), duration);
	}

	Animate* Animate::move(const Vector3 &vec, double duration){
		return AnimatePosition::move(vec, duration);
	}

	Animate* Animate::moveTo(float x, float y, float z, double duration){
		return AnimatePosition::moveTo(Vector3(x, y, z), duration);
	}

	Animate* Animate::moveTo(const Vector3 &pos, double duration){
		return AnimatePosition::moveTo(pos, duration);
	}

	Animate* Animate::rotate(float degree, const Vector3 &vec){
		return AnimateRotation::rotate(degree, vec);
	}
	
	Animate* Animate::rotate(float degree, const Axis &axis){
		return AnimateRotation::rotate(degree, axis);
	}

	Animate* Animate::rotateTo(const Quaternion &quat){
		return AnimateRotation::rotateTo(quat);
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

	Animate* Animate::fadeTo(double opacity, double duration){
		return AnimateOpacity::fadeTo(opacity, duration);
	}

	Animate* Animate::show(double duration){
		return Animate::fadeTo(1, duration);
	}

	Animate* Animate::hide(double duration){
		return Animate::fadeTo(0, duration);
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
		_beginTime = -1;
		_duration = 0;
		_bounces = 1;
		_repeats = 1;
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

	double Animate::duration() const{
		return _duration;
	}
	
	void Animate::duration(double duration){
		_duration = duration;
	}

	double Animate::beginTime() const{
		return _beginTime;
	}

	void Animate::beginTime(double beginTime){
		_beginTime = beginTime;
	}

	void Animate::callback(AnimateCallback func, void *ctx){
		_callback = func;
		_callbackCtx = ctx;
	}
	
	float Animate::bounces() const{
		return _bounces;
	}

	void Animate::bounces(float count){
		_bounces = count;
	}

	int Animate::repeats() const{
		return _repeats;
	}

	void Animate::repeats(int count){
		_repeats = count;
	}

	void Animate::repeat(bool enable){
		_repeats = enable? -1 : 1;
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
		if(_bounces != 1){
			// 通过反函数计算当前时间是第几跳
			double bounce_ratio = reverse_timing_func(_bounceFunc, p);
			// 相邻的两次组成一次周期
			step_s = floor(bounce_ratio * _bounces/2) * 2; // 向下取偶
			step_e = step_s+2;
			// 周期的开始和结束时间
			double time_s = _bounceFunc(step_s/_bounces);
			double time_e = _bounceFunc(step_e/_bounces);
			
			p = (p - time_s)/(time_e - time_s);
			p = (p < 0.5)? 2 * p : 2 * (1-p);
		}
		
		double y = _easingFunc(p);
		
		if(_bounces != 1){
			double total_steps = ceil(_bounces/2) * 2; // 向上取偶
			y *= _accelateFunc(step_e/total_steps);
		}
		return y;
	}

	void Animate::updateAtTime(double time, Node *target){
		if(time < _beginTime){
			return;
		}

		if(_state == AnimateStateNone){
			if(_beginTime == -1){
				// auto start
				_beginTime = time;
			}
			if(time >= _beginTime){
				this->state(AnimateStateBegan);
			}
		}
		if(_state == AnimateStateBegan || _state == AnimateStateDidUpdate){
			double progress;
			double timing_p;
			if(time >= _beginTime + _duration){
				progress = 1;
				timing_p = 1;
			}else{
				progress = (time - _beginTime)/_duration;
				progress = fmin(1, progress);
				timing_p = this->timing(progress);
			}

			this->state(AnimateStateWillUpdate);
			update(timing_p, target);
			this->state(AnimateStateDidUpdate);

			if(progress >= 1){
				_repeats --;
				if(_repeats == 0){
					this->state(AnimateStateEnded);
				}else{
					_beginTime = time;
				}
			}
		}
	}

}; // end namespace
