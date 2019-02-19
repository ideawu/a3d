//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Scene_hpp
#define a3d_Scene_hpp

#include <map>
#include "Node.h"
#include "Camera.h"
#include "Context.h"
#include "Drawable.h"
#include "Color.h"

namespace a3d{
	class Scene
	{
	public:
		static Scene* create();
		static Scene* createWith(Context *context, Drawable *drawable);

		~Scene();

		Context* context() const;
		Drawable* drawable() const;
		Camera* camera() const;

		double time() const;
		void time(double time);
		
		// 使用指定层开始绘图
		void layer(int index);

		// 返回当前 layer 的 rootNode
		Node* rootNode();
		// node 内存不由 Scene 管理
		void addNode(Node *node);
		void removeNode(Node *node);

		void view3D();
		void view2D();

		void render(); // render at current time
		void renderAtTime(double time);

	private:
		Scene();
		Scene(const Scene &d);
		Scene& operator =(const Scene &d);
		
		double _time;
		Context *_context;
		Drawable *_drawable;
		Camera *_camera;
		Color _backgroundColor;
		
		Node *_rootNode;
		std::map<int, Node*> _layers;
	};
}; // end namespace

#endif /* Scene_hpp */
