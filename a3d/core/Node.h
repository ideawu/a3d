//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include <list>
#include "Object.h"
#include "Animate.h"

namespace a3d{
	class NodeAnimation;
	
 	class Node : public Object
	{
	public:
		Node();
		virtual ~Node();

		// 子类实现此方法，但子类的使用者不直接调用此方法，而是调用 render()。
		virtual void draw(){};

		Node* parent() const;
		void removeFromParent();
		void addSubNode(Node *node);
		void removeSubNode(Node *node);
		
		void render(); // renderAtTime(-1)
		void renderAtTime(float time);

		// action 内存由 Node 管理
		void runAnimation(Animate *action);
		// 移除指定的动画，注意：并释放其内存！
		void removeAnimation(Animate *action);
		// 移除所有动画，释放内存
		void removeAllAnimations();
		bool hasAnimations();

	protected:
		void pushMatrix();
		void popMatrix();
		
	private:
		Node(const Node &d);
		Node& operator =(const Node& d);
		
		Node *_parent;
		std::list<Node *> *_subs;
		NodeAnimation *_animation;
		
		void updateAnimationAtTime(float time);
	};

	
	// 辅助类
	class NodeAnimation
	{
	public:
		Node origin;
		Node current;
		// 基于性能考虑，std::list 的节点应该保存自身的 iterator 以便快速删除，但这里不考虑
		std::list<Animate *> actions;
	};

}; // end namespace

#endif /* Drawable_hpp */
