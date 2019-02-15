//  Created by ideawu on 18-1-28.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Clock.h"

namespace a3d{
	enum{
		INVALID, PAUSED, STOP, RUNNING
	};
	static const int INVALID_TICK = 999999999.0;

	Clock::Clock(){
		_state = RUNNING;
		_firstTick = INVALID_TICK;
		_lastTick = INVALID_TICK;
		_speed = 1;
	}

	double Clock::time() const{
		return _speed * (_lastTick - _firstTick);
	}

	void Clock::time(double time){
		_firstTick = _lastTick - time/_speed;
	}

	float Clock::speed() const{
		return _speed;
	}
	
	void Clock::speed(float speed){
		double time = this->time();
		_speed = speed;
		this->time(time);
	}

	void Clock::update(double tick){
		if(isStopped()){
			return;
		}else if(isPaused()){
			double time = this->time();
			_lastTick = tick;
			this->time(time);
		}else{
			if(_firstTick == INVALID_TICK){
				_firstTick = tick;
			}
			_lastTick = tick;
		}
	}

	bool Clock::isRunning() const{
		return _state == RUNNING;
	}
	
	bool Clock::isPaused() const{
		return _state == PAUSED;
	}
	
	bool Clock::isStopped() const{
		return _state == STOP;
	}

	void Clock::start(){
		_state = RUNNING;
	}

	void Clock::pause(){
		_state = PAUSED;
	}

	void Clock::stop(){
		_state = STOP;
		_firstTick = INVALID_TICK;
		_lastTick = INVALID_TICK;
	}

}; // end namespace
