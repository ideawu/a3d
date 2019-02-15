//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Node.h"
#include "Animator.h"
#include "Renderer.h"

namespace a3d{

	Node::Node(){
		_parent = NULL;
		_subs = NULL;
		_animator = NULL;
		_clipBounds = false;
	}

	Node::Node(const Node &d){
		Node();
		*this = d;
	}

	Node& Node::operator =(const Node &d){
		Object::operator=(d);
		return *this;
	}

	Node::~Node(){
		if(_parent){
			removeFromParent();
		}
		delete _subs;
		delete _animator;
	}

	bool Node::visible() const{
		return !hidden() && (!_parent || _parent->visible());
	}

	bool Node::clipBounds() const{
		return _clipBounds;
	}
	
	void Node::clipBounds(bool clip){
		_clipBounds = clip;
	}

	
	Node* Node::parent() const{
		return _parent;
	}
	
	void Node::removeFromParent(){
		if(_parent){
			_parent->removeSubnode(this);
		}
	}
	
	void Node::addSubnode(Node *node){
		addSubnode(node, false);
	}
	
	void Node::addSubnode(Node *node, bool isFront){
		if(!_subs){
			_subs = new std::list<Node *>();
		}
		if(isFront){
			this->insertSubnodeAtIndex(node, (int)_subs->size());
		}else{
			this->insertSubnodeAtIndex(node, 0);
		}
	}

	void Node::insertSubnodeAtIndex(Node *node, int index){
		if(!_subs){
			_subs = new std::list<Node *>();
		}
		if(node->_parent){
			if(node->_parent == this){
				return;
			}else{
				node->removeFromParent();
			}
		}
		node->_parent = this;

		if(index >= _subs->size()){
			_subs->push_back(node);
		}else if(index <= 0){
			_subs->push_front(node);
		}else{
			std::list<Node*>::iterator it=_subs->begin();
			for(int i=0; i<index; i++){
				it ++;
			}
			_subs->insert(it, node);
		}
	}

	void Node::removeSubnode(Node *node){
		if(!_subs){
			return;
		}
		if(node->_parent == this){
			node->_parent = NULL;
			_subs->remove(node);
		}
	}

	void Node::bringSubnodeToBack(Node *node){
		removeSubnode(node);
		addSubnode(node, false);
	}
	
	void Node::bringSubnodeToFront(Node *node){
		removeSubnode(node);
		addSubnode(node, true);
	}

	Matrix4 Node::worldMatrix() const{
		Matrix4 mat = this->matrix();
		if(_parent){
			mat = _parent->worldMatrix().mul(mat);
		}
		return mat;
	}

	Vector3 Node::convertVectorToWorld(const Vector3 &vec) const{
		return this->worldMatrix().mul(vec);
	}
	
	Point3 Node::convertPointToWorld(const Point3 &pos) const{
		return this->worldMatrix().mul(pos);
	}
	
	Vector3 Node::convertVectorFromWorld(const Vector3 &vec) const{
		return this->worldMatrix().invert().mul(vec);
	}
	
	Point3 Node::convertPointFromWorld(const Point3 &pos) const{
		return this->worldMatrix().invert().mul(pos);
	}
	
	Axis Node::convertAxisToWorld(const Axis &axis) const{
		Point3 p = convertPointToWorld(axis.origin);
		Vector3 v = convertVectorToWorld(axis.direction);
		return Axis(p, v);
	}
	
	Axis Node::convertAxisFromWorld(const Axis &axis) const{
		Point3 p = convertPointFromWorld(axis.origin);
		Vector3 v = convertVectorFromWorld(axis.direction);
		return Axis(p, v);
	}
	
	void Node::draw(){
	}

	void Node::updateAtTime(double time){
		if(_animator){
			_animator->updateAtTime(time);
		}
	}
	
	void Node::renderAtTime(double time){
		this->updateAtTime(time);
		
		bool parentVisible = Renderer::current()->opacity() > 0;
		if(parentVisible){
			Renderer::current()->pushOpacity(this->opacity());
		}
		bool currentVisible = Renderer::current()->opacity() > 0;
		if(currentVisible){
			Renderer::current()->pushMatrix(this->matrix());
#if 0
			{
				int level = 0;
				Node *p = this;
				while(p->parent()){
					p = p->parent();
					level ++;
				}
				char buf[256];
				int w = 2;
				for(int i=0; i<level*w; i+=w){
					buf[i] = ' ';
					buf[i+1] = ' ';
				}
				buf[level*w] = '\0';
				int subs = _subs? (int)_subs->size() : 0;
				log_debug("%s %d, subs: %d", buf, this, subs);
			}
#endif
			if(_clipBounds){
				Renderer::current()->pushStencil();
			}
			this->draw();
			if(_clipBounds){
				Renderer::current()->bindStencil();
			}
		}
		if(_subs){
			// 如果完全透明则不渲染，但仍调用子节点renderAtTime()更新动画
			for(std::list<Node*>::iterator it=_subs->begin(); it != _subs->end(); it++){
				Node *node = *it;
				node->renderAtTime(time);
			}
		}
		if(currentVisible){
			if(_clipBounds){
				Renderer::current()->popStencil();
			}
			Renderer::current()->popMatrix();
		}
		if(parentVisible){
			Renderer::current()->popOpacity();
		}
	}


	Animator* Node::animator(){
		if(!_animator){
			_animator = Animator::create(this);
		}
		return _animator;
	}

	bool Node::isAnimating() const{
		return _animator && _animator->isAnimating();
	}

	void Node::startAnimation(){
		animator()->startAnimation();
	}

	void Node::stopAnimation(){
		animator()->stopAnimation();
	}

	void Node::toggleAnimation(){
		animator()->toggleAnimation();
	}

	void Node::runAnimation(Animate *action){
		animator()->runAnimation(action);
	}
	
	void Node::removeAnimation(Animate *action){
		animator()->removeAnimation(action);
	}

	void Node::removeAllAnimations(){
		animator()->removeAllAnimations();
	}
	
	bool Node::hasAnimations() const{
		return _animator && _animator->hasAnimations();
	}

}; // end namespace
