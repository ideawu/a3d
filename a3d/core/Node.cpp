//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Node.h"
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
		if(_animation){
			removeAllAnimations();
			delete _animation;
		}
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
			node->removeFromParent();
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

	void Node::pushMatrix(){
		glPushMatrix();
		glMultMatrixf((const GLfloat *)this->matrix().array());
	}
	
	void Node::popMatrix(){
		glPopMatrix();
	}

	void Node::render(){
		renderAtTime(-1);
	}
	
	void Node::updateAnimationAtTime(float time){
		if(time < 0){
			return;
		}
		
		if(_animation && _animation->actions.size() > 0){
			Node *origin = &_animation->origin;
			Node *current = &_animation->current;
			
			// 动画进行前，检查 current 和 this，将 diff 更新到 origin 中，因为动画进行过程中，this 可能被更新
			Transform trans = Transform::transformBetween(*current, *this);
			origin->transform(trans);
			
			std::list<Animate*> *actions = &_animation->actions;
			for(std::list<Animate*>::iterator it=actions->begin(); it != actions->end(); /**/){
				Animate *action = *it;
				action->updateAtTime(time, current, origin);
				if(action->state() == AnimateStateEnd){
					it = actions->erase(it);
					delete action;
				}else{
					it ++;
				}
			}
			// 动画进行时，同时更新 current 和 this
			*this = *current;
		}
	}

	void Node::renderAtTime(float time){
		this->updateAnimationAtTime(time);

		// 如果完全透明则不渲染，但仍更新动画
		if(Renderer::current()->opacity() != 0){
			if(_opacity != 1){
				Renderer::current()->pushOpacity(_opacity);
			}
			pushMatrix();
			
			this->draw();
		}
		if(_subs){
			for(std::list<Node*>::iterator it=_subs->begin(); it != _subs->end(); it++){
				Node *node = *it;
				node->renderAtTime(time);
			}
		}
		if(Renderer::current()->opacity() != 0){
			if(_opacity != 1){
				Renderer::current()->popOpacity();
			}
			popMatrix();
		}
	}

	void Node::runAnimation(Animate *action){
		if(!_animation){
			_animation = new NodeAnimation();
		}
		// 如果所有的动画都未开始，则应该在开始前，设置 origin
		if(_animation->actions.empty()){
			_animation->origin = *this;
			_animation->current = *this;
		}
		_animation->actions.push_back(action);
	}
	
	void Node::removeAnimation(Animate *action){
		if(!_animation){
			return;
		}
		_animation->actions.remove(action);
		delete action;
	}

	void Node::removeAllAnimations(){
		if(!_animation){
			return;
		}
		std::list<Animate*> *actions = &_animation->actions;
		for(std::list<Animate*>::iterator it=actions->begin(); it != actions->end(); it++){
			Animate *action = *it;
			delete action;
		}
		_animation->actions.clear();
	}
	
	bool Node::hasAnimations(){
		if(!_animation){
			return false;
		}
		return !_animation->actions.empty();
	}

}; // end namespace
