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

	void SpriteNode::updateAtTime(double time){
		// 调用父方法
		Node::updateAtTime(time);
		
		double lastTime = _clock.time();
		_clock.update(time);
		if(!isPlaying()){
			return;
		}
		if(!_sprite){
			return;
		}
		double thisTime = _clock.time();
		
		// 修正 looping 时钟到 [0, duration]
		if(_isLooping && _sprite->duration() > 0){
			if(thisTime < 0){
				thisTime = fabs(thisTime + _sprite->duration());
			}
			thisTime = fmod(thisTime, _sprite->duration());
//			while(thisTime > _sprite->duration()){
//				thisTime -= _sprite->duration();
//			}
			if(thisTime != _clock.time()){
				_clock.time(thisTime);
			}
		}

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

	void SpriteNode::draw(){
		if(!_sprite){
			return;
		}
		Texture *texture = _sprite->textureAtTime(_clock.time());
		if(texture){
			Frame texRect = Frame(0, 0, 1, 1);
			Frame verRect = Frame(-this->width()/2, -this->height()/2, this->width(), this->height());
			texture->draw(texRect, verRect);
		}
	}
	
}; // end namespace

