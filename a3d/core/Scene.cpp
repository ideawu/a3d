//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Scene.h"

namespace a3d{
	
	Scene* Scene::create(){
		return Scene::createWith(Context::createShared(), Drawable::createShared());
	}
	
	Scene* Scene::createWith(Context *context, Drawable *drawable){
		int width = drawable->width();
		int height = drawable->height();
		
		Scene *ret = new Scene();
		ret->_context = context;
		ret->_drawable = drawable;
		ret->_camera->setup(60, width, height, width*10, -width/2);
		return ret;
	}

	Scene::Scene(){
		_context = NULL;
		_drawable = NULL;
		_camera = new Camera();
		_backgroundColor = Color::clear();
		_layer = 0;
	}
	
	Scene::~Scene(){
		removeAllNodes();
		delete _camera;
		delete _drawable;
		delete _context;
	}
	
	Context* Scene::context() const{
		return _context;
	}

	Drawable* Scene::drawable() const{
		return _drawable;
	}

	Camera* Scene::camera() const{
		return _camera;
	}

	Color Scene::backgroundColor() const{
		return _backgroundColor;
	}
	
	void Scene::backgroundColor(const Color &color){
		_backgroundColor = color;
	}

	double Scene::time() const{
		return _time;
	}
	
	void Scene::time(double time){
		_time = time;
	}
	
	void Scene::layer(int index){
		_layer = index;
	}

	Node* Scene::rootNode(){
		Node *root = _layers[_layer];
		if(!root){
			root = new Node();
			_layers[_layer] = root;
		}
		return root;
	}

	void Scene::addNode(Node *node){
		rootNode()->addSubnode(node);
	}
	
	void Scene::removeNode(Node *node){
		rootNode()->removeSubnode(node);
	}
	
	void Scene::removeAllNodes(){
		for(std::map<int, Node*>::iterator it = _layers.begin(); it != _layers.end(); it++){
			Node *node = it->second;
			delete node;
		}
		_layers.clear();
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
		_drawable->clearColor(_backgroundColor);

		for(std::map<int, Node*>::iterator it = _layers.begin(); it != _layers.end(); it++){
			_drawable->clearDepth();
			Node *node = it->second;
			node->renderAtTime(time);
		}
		
//		_drawable->finish();
	}

}; // end namespace
