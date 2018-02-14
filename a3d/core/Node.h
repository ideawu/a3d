//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Node_hpp
#define a3d_Node_hpp

#include <list>
#include "Object.h"

namespace a3d{
	class Animate;
	class Animator;
	
 	class Node : public Object
	{
	public:
		Node();
		virtual ~Node();

		// 子类方法
		virtual void draw(){};
		virtual void drawAtTime(double time){draw();};

		void render(); // renderAtTime(0);
		void renderAtTime(double time);

		float opacity() const;
		void opacity(float opacity);
		void show();
		void hide();
		bool hidden() const;
		bool visible() const; // 结合父节点判断是否可见

		Node* parent() const;
		void removeFromParent();
		void addSubnode(Node *node);
		// index 0 is back
		void addSubnodeAtIndex(Node *node, int index);
		void removeSubnode(Node *node);
		void bringSubnodeToBack(Node *node);
		void bringSubnodeToFront(Node *node);

		// 当前节点在世界（即根节点上一级）坐标系中的矩阵
		Matrix4 worldMatrix() const;
		// ### 与世界坐标系的转换
		Vector3 convertVectorToWorld(const Vector3 &vec) const;
		Vector3 convertVectorFromWorld(const Vector3 &vec) const;
		Point3 convertPointToWorld(const Point3 &pos) const;
		Point3 convertPointFromWorld(const Point3 &pos) const;
		Axis convertAxisToWorld(const Axis &axis) const;
		Axis convertAxisFromWorld(const Axis &axis) const;

		// ### 动画管理
		// action 内存由 Node 管理
		void runAnimation(Animate *action);
		// 移除指定的动画，注意：并释放其内存！
		void removeAnimation(Animate *action);
		// 移除所有动画，释放内存
		void removeAllAnimations();
		bool hasAnimations() const;

	private:
		friend class Animator;
		
		Node(const Node &d);
		Node& operator =(const Node &d);
		
		float _opacity;
		
		Node *_parent;
		std::list<Node*> *_subs;
		Animator *_animator;

		void addSubnode(Node *node, bool isFront);
	};

}; // end namespace

#endif /* Drawable_hpp */
