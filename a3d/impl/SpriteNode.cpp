//  Created by ideawu on 18-1-28.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#include "SpriteNode.h"

namespace a3d{
	enum{
		SpritePlaying,
		SpritePaused,
		SpriteStopped
	};
	
	SpriteNode::SpriteNode(){
		_sprite = NULL;
		_isFrameLossless = false;
		_isLooping = true;
		_state = SpritePlaying;
	}
	
	SpriteNode::~SpriteNode(){
		delete _sprite;
	}

	Sprite* SpriteNode::sprite() const{
		return _sprite;
	}
	
	void SpriteNode::sprite(Sprite *sprite){
		if(_sprite){
			delete _sprite;
		}
		_sprite = sprite;
		if(_sprite){
			this->size(_sprite->size());
		}
	}

	void SpriteNode::play(){
		if(isPlaying()){
			return;
		}
		_state = SpritePlaying;
		_clock.resume();
	}
	
	void SpriteNode::pause(){
		if(!isPlaying()){
			return;
		}
		_state = SpritePaused;
		_clock.pause();
	}
	
	void SpriteNode::stop(){
		if(isStopped()){
			return;
		}
		_state = SpriteStopped;
		_clock.reset();
	}
	
	bool SpriteNode::isPlaying() const{
		return _state == SpritePlaying;
	}
	
	bool SpriteNode::isPaused() const{
		return _state == SpritePaused;
	}
	
	bool SpriteNode::isStopped() const{
		return _state == SpriteStopped;
	}

	void SpriteNode::isFrameLossless(bool isLossless){
		_isFrameLossless = isLossless;
	}
	
	void SpriteNode::isLooping(bool looping){
		_isLooping = looping;
	}

	void SpriteNode::updateClock(double time){
		if(isStopped()){
			return;
		}
		double lastRenderTime = _clock.time();
		_clock.update(time);
		if(isPaused()){
			return;
		}
		
		double thisRenderTime = _clock.time();
		
		double lastDuration = 0;
		int lastFrame = sprite()->frameAtTime(lastRenderTime, &lastDuration);
		if(lastFrame == -1){
			lastFrame = 0;
		}
		
		// 不丢帧
		if(_isFrameLossless && sprite()->duration() > 0){
			double nextRenderTime = lastRenderTime + lastDuration;
			if(thisRenderTime > nextRenderTime){
				thisRenderTime = nextRenderTime;
				_clock.time(thisRenderTime);
				//				log_debug("%f %f", _clock.time(), time);
			}
		}
		
		// 重复播放
		if(_isLooping && sprite()->duration() > 0){
			if(thisRenderTime >= sprite()->duration()){
				thisRenderTime = 0;
				_clock.time(thisRenderTime);
				//				log_debug("%f %f", _clock.time(), time);
			}
		}
	}
	
	void SpriteNode::drawAtTime(double time){
		if(!sprite()){
			return;
		}
		this->updateClock(time);
		
		Texture *texture = sprite()->textureAtTime(_clock.time());
		if(texture){
			Rect texRect = Rect(0, 0, 1, 1);
			Rect vertRect = Rect(-this->width()/2, -this->height()/2, this->width(), this->height());
			texture->draw(texRect, vertRect);
		}
	}
	
}; // end namespace

