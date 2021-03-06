//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Animator_hpp
#define a3d_Animator_hpp

#include <list>
#include "Animate.h"
#include "Clock.h"

namespace a3d{
	class Animator
	{
	public:
		static Animator* create(Node *target);

		~Animator();

		double time() const;

		bool isAnimating() const;
		void startAnimation();
		void stopAnimation();
		void toggleAnimation();
		void runAnimation(Animate *action);
		void removeAnimation(Animate *action);
		void removeAllAnimations();
		bool hasAnimations() const;

		void updateAtTime(double time);

	private:
		Animator();
		Animator(const Animator &d);
		Animator& operator =(const Animator &d);

		Clock _clock;

		Node *_target;
		Node _origin;
		Node _current;
		
		// 基于性能考虑，std::list 的节点应该保存自身的 iterator 以便快速删除，但这里不考虑
		std::list<Animate*> _actions;
	};
}; // end namespace

#endif /* NodeAnimation_hpp */
