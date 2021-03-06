//  Created by ideawu on 18-1-28.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Clock_h
#define a3d_Clock_h

// 注意！时间要用双精度！

namespace a3d{
	// 用于将世界 tick 转成本地时间
	class Clock
	{
	public:
		Clock();

		double time() const;
		void time(double time);
		// 在第一次调用 update 时，自动初始化
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
		int _state;
		double _firstTick;
		double _lastTick;
		float _speed;
	};
}; // end namespace

#endif /* defined(__a3d__Clock__) */
