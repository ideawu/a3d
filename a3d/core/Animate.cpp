//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Animate.h"

namespace a3d{
	Animate::Animate(){
		_state = AnimateStateNone;
		_timingFunc = NULL;
		_callback = NULL;
		_beginTime = -1;
		_currentTime = -1;
		_duration = 0;
	}
	
	Animate::~Animate(){
	}

	AnimateState Animate::state() const{
		return _state;
	}

	void Animate::updateState(AnimateState state){
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
			float timing_p;
			if(_duration == 0){
				// 不管时间如何，如果 duration 为零则立即执行
				progress = 1;
				timing_p = 1;
			}else if(time < _beginTime){
				return;
			}else{
				progress = (time - _beginTime)/_duration;
				progress = fmin(1, progress);
				timing_p = _timingFunc? _timingFunc(progress) : AnimateTimingEaseOut(progress);
			}
			_currentTime = time;

			updateState(AnimateStateWillUpdate);
			update(timing_p, current, origin);
			updateState(AnimateStateDidUpdate);

			if(progress >= 1){
				updateState(AnimateStateEnd);
			}
		}
	}

}; // end namespace
