//  Created by ideawu on 02/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "AnimationTypes.h"

namespace a3d{
	
	inline static double TimingFuncNone_(double p){
		return 1;
	}
	inline static double TimingFuncLinear_(double p){
		return p;
	}
	inline static double TimingFuncEaseIn_(double p){
		return p * p;
	}
	inline static double TimingFuncEaseOut_(double p){
		return 1 - TimingFuncEaseIn(1-p); // 通用
	}
	inline static double TimingFuncEaseInOut_(double p){
		// 通用，只需要替换 in 和 out，即可组合任意的 inout
		if(p < 0.5){
			p = p * 2;
			return TimingFuncEaseIn(p)/2;
		}else{
			p = (p - 0.5) * 2;
			return TimingFuncEaseOut(p)/2 + 0.5;
		}
	}
	inline static double TimingFuncLoop_(double p){
		return sinf(p * M_PI);
	}
	inline static double TimingFuncSwing_(double p){
		return sinf(p * M_PI * 2);
	}
	
	TimingFunc TimingFuncNone = TimingFuncNone_;
	TimingFunc TimingFuncLinear = TimingFuncLinear_;
	TimingFunc TimingFuncEaseIn = TimingFuncEaseIn_;
	TimingFunc TimingFuncEaseOut = TimingFuncEaseOut_;
	TimingFunc TimingFuncEaseInOut = TimingFuncEaseInOut_;
	TimingFunc TimingFuncLoop = TimingFuncLoop_;
	TimingFunc TimingFuncSwing = TimingFuncSwing_;

}; // end namespace
