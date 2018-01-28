//  Created by ideawu on 18-1-28.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Clock.h"

namespace a3d{

	Clock::Clock(){
		reset();
	}

	float Clock::time() const{
		return _speed * (_secondTick - _firstTick);
	}

	void Clock::time(float time){
		_firstTick = _secondTick - time/_speed;
	}

	void Clock::update(float tick){
		if(isStopped()){
			_pauseTick = tick;
		}else{
			if(_firstTick == 0){
				_firstTick = tick;
			}
			_secondTick = tick;
		}
	}

	void Clock::start(){
		if(isStopped()){
			float time = this->time();
			_secondTick = _pauseTick;
			this->time(time);
			_pauseTick = 0;
		}
	}

	void Clock::stop(){
		if(isStarted()){
			_pauseTick = _secondTick;
		}
	}

	void Clock::reset(){
		_firstTick = 0;
		_secondTick = 0;
		_pauseTick = 0;
		_speed = 1;
	}

	bool Clock::isStarted() const{
		return _pauseTick == 0;
	}

	bool Clock::isStopped() const{
		return _pauseTick != 0;
	}

	float Clock::speed() const{
		return _speed;
	}

	void Clock::speed(float speed){
		float time = this->time();
		_speed = speed;
		this->time(time);
	}

	float Clock::secondTick() const{
		return _secondTick;
	}

}; // end namespace
