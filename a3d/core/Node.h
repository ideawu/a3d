//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include <list>
#include "Object.h"

namespace a3d{
	class Animate;
	class NodeAnimateHelper;
	
 	class Node : public Object
	{
	public:
		Node();
		virtual ~Node();

		// 子类实现两个方法中的一个即可。
		virtual void draw(){};
		virtual void drawAtTime(float time){draw();};

		void render(); // renderAtTime(-1)
		void renderAtTime(float time);

		float opacity() const;
		void opacity(float opacity);

		Node* parent() const;
		void removeFromParent();
		void addSubNode(Node *node);
		void removeSubNode(Node *node);

		// action 内存由 Node 管理
		void runAnimation(Animate *action);
		// 移除指定的动画，注意：并释放其内存！
		void removeAnimation(Animate *action);
		// 移除所有动画，释放内存
		void removeAllAnimations();
		bool hasAnimations();

	private:
		friend class NodeAnimateHelper;
		
		Node(const Node &d);
		Node& operator =(const Node& d);
		
		float _opacity;
		
		Node *_parent;
		std::list<Node *> *_subs;
		NodeAnimateHelper *_animation;
		
		void updateAnimationAtTime(float time);
	};

}; // end namespace

#endif /* Drawable_hpp */
