//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include "Object.h"
#include "Animate.h"

namespace a3d{
	class NodeAnimate;
	
 	class Node : public Object
	{
	public:
		Node();
		~Node();

		// 子类实现此方法，但子类的使用者不直接调用此方法，而是调用 render()。
		virtual void draw(){};
		
		void render();
		void render(float time);

	protected:
		void pushMatrix();
		void popMatrix();
		
	private:
		Node(const Node &d){}
		
		///// 动画
	public:
		void runAnimation(const Animate &animate);
		void removeAllAnimations();
		bool hasAnimations();
	private:
		NodeAnimate *_animate;
	};
	
}; // end namespace

#endif /* Drawable_hpp */
