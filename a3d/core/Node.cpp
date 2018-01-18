//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Node.h"

namespace a3d{
	Node::Node(){
		_parent = NULL;
		_subs = NULL;
		_animation = NULL;
	}

	Node::Node(const Node &d) : Object(d){
		_parent = NULL;
		_subs = NULL;
		_animation = NULL;
	}
	
	Node& Node::operator =(const Node& d){
		Object::operator=(d);
		return *this;
	}

	Node::~Node(){
		if(_subs){
			delete _subs;
		}
		if(_animation){
			std::vector<Animate*> *actions = &_animation->actions;
			for(std::vector<Animate*>::iterator it=actions->begin(); it != actions->end(); it++){
				Animate *action = *it;
				delete action;
			}
			delete _animation;
		}
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
			_subs = new std::vector<Node *>();
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
		for(std::vector<Node*>::iterator it=_subs->begin(); it != _subs->end(); it++){
			const Node *n = *it;
			if(n == node){
				node->_parent = NULL;
				_subs->erase(it);
				return;
			}
		}
	}

	void Node::pushMatrix(){
		glPushMatrix();
		glMultMatrixf((const GLfloat *)this->matrix());
	}
	
	void Node::popMatrix(){
		glPopMatrix();
	}

	void Node::render(){
		renderAtTime(-1);
	}

	void Node::renderAtTime(float time){
		if(time >= 0 && _animation && _animation->actions.size() > 0){
			Node *origin = &_animation->origin;
			Node *current = &_animation->current;
			
			// 动画进行前，检查 current 和 this，将 diff 更新到 origin 中，因为动画进行过程中，this 可能被更新
			Transform trans = Transform::transformBetween(*current, *this);
			origin->transform(trans);

			std::vector<Animate*> *actions = &_animation->actions;
			for(std::vector<Animate*>::iterator it=actions->begin(); it != actions->end(); /**/){
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
		
		pushMatrix();
		draw();
		popMatrix();
	}

	void Node::runAnimation(Animate *action){
		if(!_animation){
			_animation = new NodeAnimate();
			_animation->origin = *this;
			_animation->current = *this;
		}
		_animation->actions.push_back(action);
	}
	
	void Node::removeAllAnimations(){
		if(!_animation){
			return;
		}
		_animation->actions.clear();
	}
	
	bool Node::hasAnimations(){
		if(!_animation){
			return false;
		}
		return _animation->actions.size() > 0;
	}

}; // end namespace
