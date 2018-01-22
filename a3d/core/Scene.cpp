//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Scene.h"

namespace a3d{
	
	Scene::Scene(){
		_context = NULL;
		_camera = new Camera();
		_rootNode = new Node();
		_rootNode->addSubNode(_camera);
	}
	
	Scene::~Scene(){
		delete _context;
		delete _camera;
		delete _rootNode;
	}
	
	Scene* Scene::create(){
		Scene *ret = new Scene();
		ret->_context = Context::shared();
		return ret;
	}

	Scene* Scene::create(Context *context){
		Scene *ret = new Scene();
		ret->_context = context;
		return ret;
	}

	Context* Scene::context() const{
		return _context;
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

	void Scene::view3D(){
		_context->loadMatrix3D(_camera->matrix3D());
	}
	
	void Scene::view2D(){
		_context->loadMatrix3D(_camera->matrix2D());
	}

	void Scene::render(){
		renderAtTime(_time);
	}

	void Scene::renderAtTime(float time){
		_time = time;
		_context->makeCurrent();
		_rootNode->renderAtTime(time);
		_context->finish();
	}

}; // end namespace
