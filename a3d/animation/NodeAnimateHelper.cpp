//  Created by ideawu on 20/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "NodeAnimateHelper.h"

namespace a3d{

	NodeAnimateHelper::NodeAnimateHelper(){
	}
	
	NodeAnimateHelper::~NodeAnimateHelper(){
		removeAll();
	}

	void NodeAnimateHelper::add(Animate *action){
		_actions.push_back(action);
	}
	
	void NodeAnimateHelper::remove(Animate *action){
		_actions.remove(action);
		delete action;
	}
	
	void NodeAnimateHelper::removeAll(){
		for(std::list<Animate*>::iterator it=_actions.begin(); it != _actions.end(); it++){
			Animate *action = *it;
			if(action->state() != AnimateStateEnd){
				action->state(AnimateStateCancelled);
			}
			delete action;
		}
		_actions.clear();
	}

	bool NodeAnimateHelper::empty() const{
		return _actions.empty();
	}
	
	void NodeAnimateHelper::updateAtTime(double time){
		// 动画进行前，检查 current 和 target，获得动画之外的变更，将 diff 更新到 origin 中
		Transform trans = Transform::transformBetween(current, *target);
//		log_debug("origin: %.2f, dw: %.2f", origin.width(), trans.size.x);
		origin.transform(trans);

		// 重置 target
		*target = origin;
		for(std::list<Animate*>::iterator it=_actions.begin(); it != _actions.end(); /**/){
			Animate *action = *it;
			// 注意，实时更新 target，最后再把 current 设置为 target
			action->updateAtTime(time, target, &origin);
			if(action->state() == AnimateStateEnd){
				it = _actions.erase(it);
				delete action;
			}else{
				it ++;
			}
		}
		// 保存 target 动画后的状态
		current = *target;
	}

}; // end namespace
