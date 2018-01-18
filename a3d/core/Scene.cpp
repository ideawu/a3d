//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Scene.h"

namespace a3d{
	
	Scene::Scene(){
	}
	
	Scene::~Scene(){
	}
	
	Scene* Scene::create(){
		Scene *ret = new Scene();
		return ret;
	}
	
	Camera* Scene::camera() const{
		return &_camera;
	}

	float Scene::time() const{
		return _time;
	}
	
	void Scene::time(float time){
		_time = time;
	}

	void Scene::addNode(Node *node){
		_rootNode.addSubNode(node);
	}
	
	void Scene::removeNode(Node *node){
		_rootNode.removeSubNode(node);
	}

}; // end namespace
