//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef NodeAnimation_hpp
#define NodeAnimation_hpp

#include <list>
#include "Node.h"
#include "Animate.h"

namespace a3d{
	// 辅助类
	class NodeAnimation
	{
	public:
		NodeAnimation();
		~NodeAnimation();
		
		void add(Animate *action);
		void remove(Animate *action);
		void removeAll();
		bool empty() const;

		void updateAtTime(float time);

	public:
		Node *target;
		Node origin;
		Node current;
		
		// 基于性能考虑，std::list 的节点应该保存自身的 iterator 以便快速删除，但这里不考虑
		std::list<Animate *> _actions;
	};
}; // end namespace

#endif /* NodeAnimation_hpp */