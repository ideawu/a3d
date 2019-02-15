//  Created by ideawu on 18-1-28.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#include "SpriteNode.h"

namespace a3d{
	
	SpriteNode::SpriteNode(){
		_sprite = NULL;
		_isFrameLossless = false;
		_isLooping = true;
		pause();
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

	void SpriteNode::updateAtTime(double time){
		// 调用父方法
		Node::updateAtTime(time);
		
		if(!_sprite){
			return;
		}
		if(isStopped()){
			return;
		}
		double lastTime = spriteTime();
		_clock.update(time);
		if(isPaused()){
			return;
		}
		double thisTime = spriteTime();
		
		// 不丢帧
		if(_isFrameLossless && _sprite->duration() > 0){
			double lastDuration = 0;
			int lastFrame = _sprite->frameAtTime(lastTime, &lastDuration);
			if(lastTime != -1){
				int thisFrame = _sprite->frameAtTime(thisTime, NULL);
				if(thisFrame == lastFrame + 1 || (_isLooping && thisFrame == 0 && lastFrame == _sprite->frames() - 1)){
					//
				}else{
					double nextTime = lastTime + lastDuration;
					_clock.time(nextTime);
				}
			}
		}
	}
	
	double SpriteNode::spriteTime() const{
		double time = _clock.time();
		if(_isLooping && _sprite && _sprite->duration() > 0){
			while(time > _sprite->duration()){
				time -= _sprite->duration();
			}
		}
		return time;
	}

	void SpriteNode::draw(){
		if(!_sprite){
			return;
		}
		Texture *texture = _sprite->textureAtTime(spriteTime());
		if(texture){
			Frame texRect = Frame(0, 0, 1, 1);
			Frame verRect = Frame(-this->width()/2, -this->height()/2, this->width(), this->height());
			texture->draw(texRect, verRect);
		}
	}
	
}; // end namespace

