//  Created by ideawu on 18-1-28.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d__Clock__h
#define a3d__Clock__h

// 注意！时间要用双精度！

namespace a3d{
	class Clock
	{
	public:
		Clock();

		double time() const;
		void time(double time);
		void update(double tick);
		
		float speed() const;
		void speed(float speed);

		bool isRunning() const;
		bool isPaused() const;
		bool isStopped() const;

		void start();
		void pause();
		void stop();

	private:
		double _firstTick;
		double _secondTick;
		double _pauseTick;
		float _speed;

		double secondTick() const;
	};
}; // end namespace

#endif /* defined(__a3d__Clock__) */
