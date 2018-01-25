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

		// 子类方法
		virtual void draw(){};
		virtual void drawAtTime(float time){draw();};

		void render(); // renderAtTime(0);
		void renderAtTime(float time);

		float opacity() const;
		void opacity(float opacity);

		Node* parent() const;
		void removeFromParent();
		void addSubNode(Node *node);
		void removeSubNode(Node *node);
		
		// ### 坐标和向量转换
		// 当前节点在世界（即根节点上一级）坐标系中的矩阵
		Matrix4 worldMatrix() const;
		Vector3 convertVectorToWorld(const Vector3 &vec) const;
		Vector3 convertVectorFromWorld(const Vector3 &vec) const;
		Vector3 convertVectorToParent(const Vector3 &vec) const;
		Vector3 convertVectorFromParent(const Vector3 &vec) const;
		Point3 convertPointToWorld(const Point3 &pos) const;
		Point3 convertPointFromWorld(const Point3 &pos) const;
		Point3 convertPointToParent(const Point3 &pos) const;
		Point3 convertPointFromParent(const Point3 &pos) const;

		// ### 动画管理
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
	};

}; // end namespace

#endif /* Drawable_hpp */
