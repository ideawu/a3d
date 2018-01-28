//  Created by ideawu on 18-1-28.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef __a3d__Clock__
#define __a3d__Clock__

namespace a3d{
	class Clock
	{
	public:
		Clock();

		float time() const;
		void time(float time);
		float speed() const;
		void speed(float speed);

		void update(float tick);

		void start();
		void stop();
		void reset();

		bool isStarted() const;
		bool isStopped() const;

		float secondTick() const;

	private:
		float _firstTick;
		float _secondTick;
		float _pauseTick;
		float _speed;
	};
}; // end namespace

#endif /* defined(__a3d__Clock__) */
