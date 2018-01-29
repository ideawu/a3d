//  Created by ideawu on 18-1-28.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef __a3d__Clock__
#define __a3d__Clock__

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

		void pause();
		void resume();
		void reset();

		bool isPaused() const;

		double secondTick() const;

	private:
		double _firstTick;
		double _secondTick;
		double _pauseTick;
		float _speed;
	};
}; // end namespace

#endif /* defined(__a3d__Clock__) */
