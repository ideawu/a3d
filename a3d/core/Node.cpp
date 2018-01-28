//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Node.h"
#include "NodeAnimateHelper.h"
#include "Renderer.h"

namespace a3d{
	Node::Node(){
		_parent = NULL;
		_subs = NULL;
		_animation = NULL;
		_opacity = 1;
	}

	Node& Node::operator =(const Node& d){
		Object::operator=(d);
		_opacity = d._opacity;
		return *this;
	}

	Node::~Node(){
		delete _subs;
		delete _animation;
	}

	float Node::opacity() const{
		return _opacity;
	}
	
	void Node::opacity(float opacity){
		_opacity = opacity;
	}

	Node* Node::parent() const{
		return _parent;
	}
	
	void Node::removeFromParent(){
		if(_parent){
			_parent->removeSubNode(this);
		}
	}
	
	void Node::addSubNode(Node *node){
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
		_subs->push_back(node);
	}
	
	void Node::removeSubNode(Node *node){
		if(!_subs){
			return;
		}
		if(node->_parent == this){
			node->_parent = NULL;
			_subs->remove(node);
		}
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

	Vector3 Node::convertVectorToParent(const Vector3 &vec) const{
		return this->matrix().mul(vec);
	}
	
	Point3 Node::convertPointToParent(const Point3 &pos) const{
		return this->matrix().mul(pos);
	}
	
	Vector3 Node::convertVectorFromParent(const Vector3 &vec) const{
		return this->matrix().invert().mul(vec);
	}
	
	Point3 Node::convertPointFromParent(const Point3 &pos) const{
		return this->matrix().invert().mul(pos);
	}


	void Node::render(){
		renderAtTime(0);
	}
	
	void Node::renderAtTime(float time){
		if(time > 0 && _animation && !_animation->empty()){
			_animation->updateAtTime(time);
			// 动画进行时，同时更新 current 和 this
			//log_debug("%f %f %f", this->width(), _animation->origin.width(), _animation->current.width());
			*this = _animation->current;
		}
		
		Renderer *renderer = Renderer::current();
		float parent_alpha = renderer->opacity();
		float node_alpha = _opacity;

		// 如果完全透明则不渲染，但仍更新动画
		if(parent_alpha != 0){
			if(node_alpha != 1){
				renderer->pushOpacity(_opacity);
			}
			renderer->pushMatrix(this->matrix());
			
			this->drawAtTime(time);
		}
		if(_subs){
			for(std::list<Node*>::iterator it=_subs->begin(); it != _subs->end(); it++){
				Node *node = *it;
				node->renderAtTime(time);
			}
		}
		if(parent_alpha != 0){
			if(node_alpha != 1){
				renderer->popOpacity();
			}
			renderer->popMatrix();
		}
	}

	void Node::runAnimation(Animate *action){
		if(!_animation){
			_animation = new NodeAnimateHelper();
			_animation->target = this;
		}
		// 如果所有的动画都未开始，则应该在开始前，设置 origin
		if(_animation->empty()){
			_animation->origin = *this;
			_animation->current = *this;
		}
		_animation->add(action);
	}
	
	void Node::removeAnimation(Animate *action){
		if(_animation){
			_animation->remove(action);
		}
	}

	void Node::removeAllAnimations(){
		if(_animation){
			_animation->removeAll();
		}
	}
	
	bool Node::hasAnimations(){
		return _animation && !_animation->empty();
	}

}; // end namespace
