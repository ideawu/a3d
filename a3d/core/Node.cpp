//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Node.h"

namespace a3d{
	Node::Node(){
		_animation = NULL;
	}

	Node::Node(const Node &d) : Object(d){
		_animation = NULL;
	}
	
	Node& Node::operator =(const Node& d){
		Object::operator=(d);
		return *this;
	}

	Node::~Node(){
		if(_animation){
			delete _animation;
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
		render(-1);
	}

	void Node::render(float time){
		if(_animation){
			if(_animation->actions.size() > 0){
				Node *target = this;
				Node *origin = &_animation->origin;
				Node *current = &_animation->current;
				
				// 动画进行前，检查 current 和 target，将 diff 更新到 origin 中，因为运动进行过程中，target 可能被更新
				
				// size 变动
				Vector3 size1 = target->size();
				Vector3 size2 = current->size();
				Vector3 size_diff = size2.sub(size1);
				Vector3 size_new = origin->size().add(size_diff);
				origin->size(size_new);
				
				// matrix 变动
				Matrix4 mat1(*target);
				Matrix4 mat2(*current);
				Matrix4 mat_diff = mat1.diff(mat2);
				origin->transform(mat_diff);
				
				for(int i=0; i<_animation->actions.size(); i++){
					Animate &animate = _animation->actions.at(i);
					animate.updateAtTime(time, current, origin);
				}
				// 动画进行时，同时更新 current 和 target
				*target = *current;
			}
		}
		
		pushMatrix();
		draw();
		popMatrix();
	}

	void Node::runAnimation(Animate animate){
		if(!_animation){
			_animation = new NodeAnimate();
			_animation->origin = *this;
			_animation->current = *this;
		}
		_animation->actions.push_back(animate);
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
