//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Camera.h"
#include "Node.h"
#include "Context.h"

namespace a3d{
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

		// node 内存不由 Scene 管理
		void addNode(Node *node);
		void removeNode(Node *node);

		void view3D();
		void view2D();

		void render();
		void renderAtTime(float time);

	private:
		Scene();
		Scene(const Scene &d);
		Scene& operator =(const Scene& d);
		
		float _time;
		Context *_context;
		Camera *_camera;
		Node *_rootNode;
	};
}; // end namespace

#endif /* Scene_hpp */
