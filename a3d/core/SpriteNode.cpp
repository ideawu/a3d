//  Created by ideawu on 18-1-28.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#include "SpriteNode.h"
#include "Texture.h"
#include "Rect.h"
#include "TextureNode.h"

namespace a3d{
	enum{
		SpritePlaying,
		SpritePaused,
		SpriteStopped
	};

	SpriteNode::SpriteNode(){
		_sprite = NULL;
		_contentNode = new TextureNode();
		this->addSubnode(_contentNode);
		_isFrameLossless = false;
		_isLooping = true;
		_state = SpritePlaying;
	}

	SpriteNode::~SpriteNode(){
		delete _sprite;
		delete _contentNode;
	}

	Node* SpriteNode::contentNode() const{
		return _contentNode;
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
			_contentNode->size(_sprite->size());
			this->size(_sprite->size());
		}
	}

	Vector3 SpriteNode::originSize() const{
		return _sprite? _sprite->size() : Vector3();
	}
	
	float SpriteNode::originWidth() const{
		return originSize().width;
	}
	
	float SpriteNode::originHeight() const{
		return originSize().height;
	}

	void SpriteNode::isFrameLossless(bool isLossless){
		_isFrameLossless = isLossless;
	}

	void SpriteNode::isLooping(bool looping){
		_isLooping = looping;
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
		int lastFrame = _sprite->frameAtTime(lastRenderTime, &lastDuration);
		if(lastFrame == -1){
			lastFrame = 0;
		}
		
		// 不丢帧
		if(_isFrameLossless && _sprite->duration() > 0){
			double nextRenderTime = lastRenderTime + lastDuration;
			if(thisRenderTime > nextRenderTime){
				thisRenderTime = nextRenderTime;
				_clock.time(thisRenderTime);
//				log_debug("%f %f", _clock.time(), time);
			}
		}
		
		// 重复播放
		if(_isLooping && _sprite->duration() > 0){
			if(thisRenderTime >= _sprite->duration()){
				thisRenderTime = 0;
				_clock.time(thisRenderTime);
//				log_debug("%f %f", _clock.time(), time);
			}
		}
	}

	void SpriteNode::drawAtTime(double time){
		if(!_sprite){
			return;
		}
		this->updateClock(time);

		Texture *texture = _sprite->textureAtTime(_clock.time());
		if(texture){
			_contentNode->texture(texture);
		}

//		float dx = (this->width() - _contentNode->width())/2 + _contentNode->x();
//		float dy = (this->height() - _contentNode->height())/2 + _contentNode->y();
//
//		Rect base, test;
//		base = Rect(0, 0, this->width(), this->height());
//		test = Rect(dx, dy, _contentNode->width(), _contentNode->height());
//		Rect viewRect = base.intersect(test);
//		if(viewRect.empty()){
//			return;
//		}
//
//		base = Rect(0, 0, _contentNode->width(), _contentNode->height());
//		test = Rect(-dx, -dy, this->width(), this->height());
//		Rect texRect = base.intersect(test);
//		if(texRect.empty()){
//			return;
//		}
////			log_debug("viewRect: %.2f %.2f %.2f %.2f", viewRect.x, viewRect.y, viewRect.width, viewRect.height);
////			log_debug("texRect: %.2f %.2f %.2f %.2f", texRect.x, texRect.y, texRect.width, texRect.height);
//
//		// 显示区域的中点
//		viewRect.x -= this->width()/2;
//		viewRect.y -= this->height()/2;
//
//		// 转成纹理归一化坐标
//		texRect.x /= _contentNode->width();
//		texRect.y /= _contentNode->height();
//		texRect.width /= _contentNode->width();
//		texRect.height /= _contentNode->height();
//		// flip image
//		texRect.y = 1 - texRect.y;
//		texRect.height = -texRect.height;
//		//	log_debug(@"texRect: %.2f,%.2f,%.2f,%.2f", texRect.x, texRect.y, texRect.width, texRect.height);
//
//		Texture *texture = _sprite->textureAtTime(_clock.time());
//		if(texture){
//			texture->draw(texRect, viewRect);
//		}
	}

}; // end namespace
