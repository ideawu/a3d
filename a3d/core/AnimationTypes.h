//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef animation_h
#define animation_h

namespace a3d{
	class Animate;
	
	typedef enum{
		AnimateStateNone,
		AnimateStateBegin,
		AnimateStateWillUpdate,
		AnimateStateDidUpdate,
		AnimateStateEnd,
		AnimateStateCancelled
	}AnimateState;

	typedef void (*AnimateCallback)(Animate *action, void *ctx);
	typedef double (*AnimateTimingFunc)(double progress);
	
	inline static double AnimateTimingNone(double p){
		return 1;
	}
	inline static double AnimateTimingLinear(double p){
		return p;
	}
	inline static double AnimateTimingEaseIn(double p){
		return p * p;
	}
	inline static double AnimateTimingEaseOut(double p){
		return 1 - AnimateTimingEaseIn(1-p); // 通用
	}
	inline static double AnimateTimingEaseInOut(double p){
		// 通用，只需要替换 in 和 out，即可组合任意的 inout
		if(p < 0.5){
			p = p * 2;
			return AnimateTimingEaseIn(p)/2;
		}else{
			p = (p - 0.5) * 2;
			return AnimateTimingEaseOut(p)/2 + 0.5;
		}
	}

	inline static double AnimateTimingLoopSine(double p){
		p = p * M_PI * 2 - M_PI_2;
		return (sinf(p) + 1)/2;
	}
}; // end namespace

#endif /* animation_h */
