//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Animate.h"

namespace a3d{
	Animate::Animate(){
		_state = AnimateStateNone;
		_target = NULL;
		_beginTime = -1;
		_duration = 0;
		_currentTime = -1;
	}
	
	Animate::Animate(const Animate &a){
		_state = a._state;
		_target = a._target;
		_beginTime = a._beginTime;
		_duration = a._duration;
		_currentTime = a._currentTime;
	}
	
	Animate::~Animate(){
	}

	AnimateState Animate::state() const{
		return _state;
	}

	void Animate::updateState(AnimateState state){
		_state = state;
	}

	void Animate::updateAtTime(float time){
		if(_state == AnimateStateNone){
			_beginTime = time;
			_currentTime = time;
			updateState(AnimateStateBegin);
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

			updateState(AnimateStateWillUpdate);
			update(progress);
			updateState(AnimateStateDidUpdate);

			if(progress == 1){
				updateState(AnimateStateEnd);
			}
		}
	}

}; // end namespace
