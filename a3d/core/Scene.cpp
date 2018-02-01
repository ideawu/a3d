//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Scene.h"
#include "Camera.h"
#include "Node.h"
#include "Context.h"

namespace a3d{
	
	Scene::Scene(){
		_context = NULL;
		_rootNode = NULL;
		_camera = new Camera();
		layer(0);
	}
	
	Scene::~Scene(){
		delete _context;
		delete _camera;
		for(std::map<int, Node*>::iterator it = _layers.begin(); it != _layers.end(); it++){
			Node *node = it->second;
			delete node;
		}
	}
	
	Scene* Scene::create(){
		Scene *ret = new Scene();
		ret->_context = Context::blankContext();
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

	void Scene::addNode(Node *node){
		_rootNode->addSubnode(node);
	}
	
	void Scene::removeNode(Node *node){
		_rootNode->removeSubnode(node);
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

	void Scene::renderAtTime(double time){
		_time = time;
		
		_context->begin();
		_context->clearColor(0, 0, 0);

		_camera->renderAtTime(time);
		
		for(std::map<int, Node*>::iterator it = _layers.begin(); it != _layers.end(); it++){
			_context->clearDepth();
			Node *node = it->second;
			node->renderAtTime(time);
		}
		
		_context->finish();
	}

}; // end namespace
