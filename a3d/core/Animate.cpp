//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Animate.h"
#include "log.h"

namespace a3d{
	Animate::Animate(){
		_state = AnimateStateNone;
		_beginTime = -1;
		_currentTime = -1;
		_duration = 0;
	}
	
	Animate::Animate(const Animate &a){
		_state = a._state;
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

	void Animate::update(float progress, Node *current, const Node *origin){
	}

	void Animate::updateAtTime(float time, Node *current, const Node *origin){
		if(_state == AnimateStateNone){
			_beginTime = time;
			_currentTime = time;
			updateState(AnimateStateBegin);
			return;
		}
		
		if(_state != AnimateStateNone && _state != AnimateStateEnd){
			if(time < _currentTime){
				return;
			}
			_currentTime = time;
			
			float progress;
			if(_duration == 0){
				progress = 1;
			}else{
				progress = (_currentTime - _beginTime)/_duration;
				if(progress >= 1 - __FLT_EPSILON__){
					progress = 1;
				}
			}
			// TODO: TimingFunc, example: progress = progress * progress
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
