//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <map>

namespace a3d{
	class Node;
	class Camera;
	class Context;
	
	class Scene
	{
	public:
		~Scene();
		static Scene* create();
		static Scene* create(Context *context);

		Context* context() const;
		Camera* camera() const;
		
		float time() const;
		void time(float time);
		
		// 使用指定层开始绘图
		void layer(int index);

		// node 内存不由 Scene 管理
		void addNode(Node *node);
		void removeNode(Node *node);

		void view3D();
		void view2D();

		void render(); // render at current time
		void renderAtTime(float time);

	private:
		Scene();
		Scene(const Scene &d);
		Scene& operator =(const Scene& d);
		
		float _time;
		Context *_context;
		Camera *_camera;
		Node *_rootNode;
		std::map<int, Node*> _layers;
	};
}; // end namespace

#endif /* Scene_hpp */
