//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Scene.h"

namespace a3d{
	
	Scene::Scene(){
		_camera = new Camera();
		_rootNode = new Node();
	}
	
	Scene::~Scene(){
		delete _camera;
		delete _rootNode;
	}
	
	Scene* Scene::create(){
		Scene *ret = new Scene();
		return ret;
	}
	
	Camera* Scene::camera() const{
		return _camera;
	}

	float Scene::time() const{
		return _time;
	}
	
	void Scene::time(float time){
		_time = time;
	}

	void Scene::addNode(Node *node){
		_rootNode->addSubNode(node);
	}
	
	void Scene::removeNode(Node *node){
		_rootNode->removeSubNode(node);
	}

	void Scene::render(){
		renderAtTime(_time);
	}

	void Scene::renderAtTime(float time){
		_time = time;
		_rootNode->renderAtTime(time);
	}

}; // end namespace
