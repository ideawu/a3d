//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_AnimationTypes_h
#define a3d_AnimationTypes_h

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
	typedef double (*TimingFunc)(double progress);
	
	// 为了编辑器自动提示友好，使用函数指针变量
	extern TimingFunc TimingFuncNone;
	extern TimingFunc TimingFuncLinear;
	extern TimingFunc TimingFuncEaseIn;
	extern TimingFunc TimingFuncEaseOut;
	extern TimingFunc TimingFuncEaseInOut;
	extern TimingFunc TimingFuncLoop;
	extern TimingFunc TimingFuncSwing;

}; // end namespace

#endif /* animation_h */
