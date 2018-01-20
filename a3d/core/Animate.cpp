//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Animate.h"

namespace a3d{
	Animate::Animate(){
		_state = AnimateStateNone;
		_timingFunc = NULL;
		_beginTime = -1;
		_currentTime = -1;
		_duration = 0;
	}
	
	Animate::Animate(const Animate &a){
		_state = a._state;
		_timingFunc = a._timingFunc;
		_beginTime = a._beginTime;
		_currentTime = a._currentTime;
		_duration = a._duration;
	}
	
	Animate::~Animate(){
	}

	AnimateState Animate::state() const{
		return _state;
	}

	void Animate::updateState(AnimateState state){
		_state = state;
		// TODO: callback
	}

	float Animate::duration() const{
		return _duration;
	}
	
	void Animate::duration(float duration){
		_duration = duration;
	}

	void Animate::timingFunc(AnimateTimingFunc func){
		_timingFunc = func;
	}

	void Animate::updateAtTime(float time, Node *current, const Node *origin){
		if(_state == AnimateStateNone){
			_beginTime = time;
			_currentTime = time;
			updateState(AnimateStateBegin);
			return;
		}
		
		if(_state != AnimateStateNone && _state != AnimateStateEnd){
			float progress;
			if(_duration == 0){
				// 不管时间如何，如果 duration 为零则立即执行
				progress = 1;
			}else if(time < _beginTime){
				return;
			}else{
				progress = (time - _beginTime)/_duration;
				progress = fmin(1, progress);
				progress = _timingFunc? _timingFunc(progress) : AnimateTimingEaseOut(progress);
				progress = fmin(1, fabs(progress));
			}
			_currentTime = time;
			
//			log_debug("progress: %f, begin time: %f, current time: %f", progress, _beginTime, _currentTime);

			updateState(AnimateStateWillUpdate);
			update(progress, current, origin);
			updateState(AnimateStateDidUpdate);

			if(progress == 1){
				updateState(AnimateStateEnd);
			}
		}
	}

}; // end namespace
