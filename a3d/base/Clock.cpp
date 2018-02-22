//  Created by ideawu on 18-1-28.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Clock.h"

namespace a3d{
	static const double INIT_TICK = 0.00001;
	static const double STOP_TICK = -1;
	static const double RUNNING_TICK = -2;

	Clock::Clock(){
		_firstTick = INIT_TICK;
		_secondTick = INIT_TICK;
		_pauseTick = RUNNING_TICK;
		_speed = 1;
	}

	double Clock::time() const{
		return _speed * (_secondTick - _firstTick);
	}

	void Clock::time(double time){
		_firstTick = _secondTick - time/_speed;
	}

	void Clock::update(double tick){
		if(isStopped()){
			return;
		}else if(isPaused()){
			_pauseTick = tick;
		}else{
			if(_firstTick == INIT_TICK){
				_firstTick = tick;
			}
			_secondTick = tick;
		}
	}

	bool Clock::isRunning() const{
		return _pauseTick == RUNNING_TICK;
	}

	bool Clock::isPaused() const{
		return _pauseTick >= INIT_TICK;
	}

	bool Clock::isStopped() const{
		return _pauseTick == STOP_TICK;
	}

	void Clock::start(){
		if(isPaused()){
			double time = this->time();
			_secondTick = _pauseTick;
			this->time(time);
		}
		_pauseTick = RUNNING_TICK;
	}

	void Clock::pause(){
		_pauseTick = _secondTick;
	}

	void Clock::stop(){
		_firstTick = INIT_TICK;
		_secondTick = INIT_TICK;
		_pauseTick = STOP_TICK;
	}

	float Clock::speed() const{
		return _speed;
	}

	void Clock::speed(float speed){
		double time = this->time();
		_speed = speed;
		this->time(time);
	}

	double Clock::secondTick() const{
		return _secondTick;
	}

}; // end namespace
