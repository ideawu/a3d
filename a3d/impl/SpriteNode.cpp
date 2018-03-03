//  Created by ideawu on 18-1-28.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#include "SpriteNode.h"

namespace a3d{
	
	SpriteNode::SpriteNode(){
		_sprite = NULL;
		_isFrameLossless = false;
		_isLooping = true;
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
		_clock.start();
	}
	
	void SpriteNode::pause(){
		_clock.pause();
	}
	
	void SpriteNode::stop(){
		_clock.stop();
	}
	
	bool SpriteNode::isPlaying() const{
		return _clock.isRunning();
	}
	
	bool SpriteNode::isPaused() const{
		return _clock.isPaused();
	}
	
	bool SpriteNode::isStopped() const{
		return _clock.isStopped();
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

		// 不丢帧
		if(_isFrameLossless && sprite()->duration() > 0){
			double lastDuration = 0;
			int lastFrame = sprite()->frameAtTime(lastRenderTime, &lastDuration);
			if(lastFrame == -1){
				lastFrame = 0;
			}

			double nextRenderTime = lastRenderTime + lastDuration;
			if(thisRenderTime > nextRenderTime){
				_clock.time(nextRenderTime);
				//log_debug("%f %f", _clock.time(), time);
			}
		}
		
		// 重复播放
		if(_isLooping && thisRenderTime >= sprite()->duration()){
			_clock.time(0);
		}
	}
	
	void SpriteNode::drawAtTime(double time){
		if(!sprite()){
			return;
		}
		this->updateClock(time);

		Texture *texture = sprite()->textureAtTime(_clock.time());
		if(texture){
			Frame texRect = Frame(0, 0, 1, 1);
			Frame verRect = Frame(-this->width()/2, -this->height()/2, this->width(), this->height());
			texture->draw(texRect, verRect);
		}
	}
	
}; // end namespace

