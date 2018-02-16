//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Animator.h"

namespace a3d{

	Animator* Animator::create(Node *target){
		Animator *ret = new Animator();
		ret->_target = target;
		ret->_origin = new Node(*target);
		ret->_current = new Node(*target);
		return ret;
	}

	Animator::Animator(){
		_target = NULL;
		_origin = NULL;
		_current = NULL;
	}
	
	Animator::~Animator(){
		delete _origin;
		delete _current;
		removeAllAnimations();
	}

	bool Animator::isAnimating() const{
		return _clock.isRunning();
	}

	void Animator::startAnimation(){
		_clock.start();
	}

	void Animator::stopAnimation(){
		_clock.pause(); // 不是 stop
	}

	void Animator::runAnimation(Animate *action){
		_actions.push_back(action);
	}
	
	void Animator::removeAnimation(Animate *action){
		_actions.remove(action);
		if(action->state() != AnimateStateEnded){
			action->state(AnimateStateCancelled);
		}
		delete action;
	}
	
	void Animator::removeAllAnimations(){
		while(!_actions.empty()){
			_actions.front();
		}
	}

	bool Animator::hasAnimations() const{
		return !_actions.empty();
	}
	
	void Animator::updateAtTime(double time){
		_clock.update(time);
		if(!isAnimating()){
			return;
		}
		if(!hasAnimations()){
			return;
		}

		// 动画进行前，检查 current 和 target，获得动画之外的变更，将 diff 更新到 origin 中
		Transform trans = Transform::transformBetween(*_current, *_target);
		_origin->transform(trans);

		// 重置 target
		*_target = *_origin;
		for(std::list<Animate*>::iterator it=_actions.begin(); it != _actions.end(); /**/){
			Animate *action = *it;

			*_current = *_target;
			action->updateAtTime(_clock.time(), _target);

			if(action->state() == AnimateStateEnded){
				// 在 current 空间里变换 origin
				Transform trans = Transform::transformBetween(*_current, *_target);
				_origin->transform(trans);

				delete action;
				it = _actions.erase(it);
			}else{
				it ++;
			}
		}
		// 保存 target 动画后的状态
		*_current = *_target;
	}

}; // end namespace
