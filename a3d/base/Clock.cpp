//  Created by ideawu on 18-1-28.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Clock.h"

namespace a3d{

	Clock::Clock(){
		_firstTick = 0;
		_secondTick = 0;
		_pauseTick = 0;
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
			if(_firstTick == 0){
				_firstTick = tick;
			}
			_secondTick = tick;
		}
	}

	bool Clock::isRunning() const{
		return _pauseTick == 0;
	}

	bool Clock::isPaused() const{
		return _pauseTick > 0;
	}

	bool Clock::isStopped() const{
		return _pauseTick == -1;
	}

	void Clock::start(){
		if(isPaused()){
			double time = this->time();
			_secondTick = _pauseTick;
			this->time(time);
		}
		_pauseTick = 0;
	}

	void Clock::pause(){
		_pauseTick = _secondTick;
	}

	void Clock::stop(){
		_firstTick = 0;
		_secondTick = 0;
		_pauseTick = -1;
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
