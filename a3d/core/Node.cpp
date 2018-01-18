//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Node.h"
#include "NodeAnimate.h"

namespace a3d{
	Node::Node(){
		_animate = NULL;
	}
	
	Node::~Node(){
		if(_animate){
			delete _animate;
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
		render(0);
	}

	void Node::render(float time){
		if(_animate){
			for(int i=0; i<_animate->actions.size(); i++){
				Animate &animate = _animate->actions.at(i);
				animate.updateAtTime(time);
			}
		}
		
		pushMatrix();
		draw();
		popMatrix();
	}

	void Node::runAnimation(const Animate &animate){
		if(!_animate){
			_animate = new NodeAnimate();
		}
		_animate->actions.push_back(animate);
	}
	
	void Node::removeAllAnimations(){
		if(!_animate){
			return;
		}
		_animate->actions.clear();
	}
	
	bool Node::hasAnimations(){
		if(!_animate){
			return false;
		}
		return _animate->actions.size() > 0;
	}

}; // end namespace
