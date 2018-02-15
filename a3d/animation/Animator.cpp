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
		if(action->state() != AnimateStateEnded){
			action->state(AnimateStateCancelled);
		}
		_actions.remove(action);
		delete action;
	}
	
	void Animator::removeAllAnimations(){
		for(std::list<Animate*>::iterator it=_actions.begin(); it != _actions.end(); it++){
			Animate *action = *it;
			if(action->state() != AnimateStateEnded){
				action->state(AnimateStateCancelled);
			}
			delete action;
		}
		_actions.clear();
	}

	bool Animator::hasAnimations() const{
		return !_actions.empty();
	}
	
	void Animator::updateAtTime(double time, bool removeEnded){
		_clock.update(time);
		if(!isAnimating()){
			return;
		}
		if(!hasAnimations()){
			return;
		}

		// 动画进行前，检查 current 和 target，获得动画之外的变更，将 diff 更新到 origin 中
		Transform trans = Transform::transformBetween(*_current, *_target);
		//log_debug("origin: %.2f, dw: %.2f", origin.width(), trans.size.x);
		_origin->transform(trans);

		// 重置 target
		*_target = *_origin;
		for(std::list<Animate*>::iterator it=_actions.begin(); it != _actions.end(); /**/){
			Animate *action = *it;
			action->updateAtTime(_clock.time(), _target);
			// 如果不 removeEned，那么就不更新 origin，因为 Ened 的动画会重新执行一遍(progress=1)。
			// 如果更新了 origin，那么时间轴回退动画重新执行时，origin又会被错误地更新一次。
			if(removeEnded && action->state() == AnimateStateEnded){
				// 将已结束的动画真正地更新原对象
				action->update(1, _origin);
				it = _actions.erase(it);
				delete action;
			}else{
				it ++;
			}
		}
		// 保存 target 动画后的状态
		*_current = *_target;
	}

}; // end namespace
