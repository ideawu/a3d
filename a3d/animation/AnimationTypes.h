//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef animation_h
#define animation_h

namespace a3d{
	typedef enum{
		AnimateStateNone,
		AnimateStateBegin,
		AnimateStateWillUpdate,
		AnimateStateDidUpdate,
		AnimateStateEnd
	}AnimateState;

	typedef float (*AnimateTimingFunc)(float progress);

	inline static float AnimateTimingEaseIn(float p){
		return p * p;
	}
	inline static float AnimateTimingEaseOut(float p){
		return 1 - AnimateTimingEaseIn(1-p); // 通用
	}
	inline static float AnimateTimingEaseInOut(float p){
		// 通用，只需要替换 in 和 out，即可组合任意的 inout
		if(p < 0.5){
			p = p * 2;
			return AnimateTimingEaseIn(p)/2;
		}else{
			p = (p - 0.5) * 2;
			return AnimateTimingEaseOut(p)/2 + 0.5;
		}
	}
}; // end namespace

#endif /* animation_h */
