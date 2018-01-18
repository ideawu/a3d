//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef NodeAnimate_hpp
#define NodeAnimate_hpp

#include <vector>
#include "Node.h"
#include "Animate.h"

namespace a3d{
	// 辅助类
	class NodeAnimate
	{
	public:
		NodeAnimate();
		~NodeAnimate();

		// TODO: 在执行动画前，保存一份状态，动画的进度根据旧状态计算，然后更新 Node，避免动画导致误差
		Node store;
		std::vector<Animate> actions;
	};
}; // end namespace

#endif /* NodeAnimate_hpp */
