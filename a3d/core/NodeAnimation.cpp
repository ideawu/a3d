//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "NodeAnimation.h"

namespace a3d{

	NodeAnimation::NodeAnimation(){
	}
	
	NodeAnimation::~NodeAnimation(){
		removeAll();
	}

	void NodeAnimation::add(Animate *action){
		_actions.push_back(action);
	}
	
	void NodeAnimation::remove(Animate *action){
		_actions.remove(action);
		delete action;
	}
	
	void NodeAnimation::removeAll(){
		for(std::list<Animate*>::iterator it=_actions.begin(); it != _actions.end(); it++){
			Animate *action = *it;
			delete action;
		}
		_actions.clear();
	}

	bool NodeAnimation::empty() const{
		return _actions.empty();
	}
	
	void NodeAnimation::updateAtTime(float time){
		// 动画进行前，检查 current 和 this，将 diff 更新到 origin 中，因为动画进行过程中，this 可能被更新
		Transform trans = Transform::transformBetween(current, *target);
		origin.transform(trans);
		
		for(std::list<Animate*>::iterator it=_actions.begin(); it != _actions.end(); /**/){
			Animate *action = *it;
			action->updateAtTime(time, &current, &origin);
			if(action->state() == AnimateStateEnd){
				it = _actions.erase(it);
				delete action;
			}else{
				it ++;
			}
		}
	}

}; // end namespace
