//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

namespace a3d{
	class Node;
	
	typedef enum{
		AnimateStateNone,
		AnimateStateBegin,
		AnimateStateWillUpdate,
		AnimateStateDidUpdate,
		AnimateStateEnd
	}AnimateState;
	
	class Animate
	{
	public:
		Animate();
		Animate(const Animate &a);
		~Animate();

		AnimateState state() const;
		float duration() const;
		void duration(float duration);

		// 子类方法
		virtual void update(float progress, Node *current, const Node *origin);

		// 根据 origin 更新 current，返回节点是否发生了更新(不是动画状态是否更新)
		bool updateAtTime(float time, Node *current, const Node *origin);
	private:
		AnimateState _state;
		float _beginTime;
		float _currentTime;
		float _duration;
		
		void updateState(AnimateState state);
	};
}; // end namespace

#endif /* Animation_hpp */
