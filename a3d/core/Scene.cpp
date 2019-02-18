//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Scene.h"

namespace a3d{
	
	Scene::Scene(){
		_context = NULL;
		_drawable = NULL;
		_rootNode = NULL;
		_camera = new Camera();
		layer(0);
	}
	
	Scene::~Scene(){
		delete _camera;
		delete _drawable;
		delete _context;
		for(std::map<int, Node*>::iterator it = _layers.begin(); it != _layers.end(); it++){
			Node *node = it->second;
			delete node;
		}
	}
	
	Scene* Scene::create(){
		Scene *ret = new Scene();
		ret->_context = Context::createShared();
		ret->_drawable = Drawable::createShared();
		return ret;
	}

	Camera* Scene::camera() const{
		return _camera;
	}

	double Scene::time() const{
		return _time;
	}
	
	void Scene::time(double time){
		_time = time;
	}
	
	void Scene::layer(int index){
		_rootNode = _layers[index];
		if(!_rootNode){
			_rootNode = new Node();
			_layers[index] = _rootNode;
		}
	}

	Node* Scene::rootNode(){
		return _rootNode;
	}

	void Scene::addNode(Node *node){
		_rootNode->addSubnode(node);
	}
	
	void Scene::removeNode(Node *node){
		_rootNode->removeSubnode(node);
	}

	void Scene::view3D(){
		_camera->view3D();
	}
	
	void Scene::view2D(){
		_camera->view2D();
	}

	void Scene::render(){
		renderAtTime(_time);
	}

	void Scene::renderAtTime(double time){
		_time = time;
		
		_context->makeCurrent();
		_camera->updateAtTime(time);
		
		_drawable->begin();
		_drawable->clearColor(0, 0, 0, 0);

		for(std::map<int, Node*>::iterator it = _layers.begin(); it != _layers.end(); it++){
			_drawable->clearDepth();
			Node *node = it->second;
			node->renderAtTime(time);
		}
		
//		_drawable->finish();
	}

}; // end namespace
