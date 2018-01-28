//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Sprite.h"
#include "ImageSprite.h"

namespace a3d{

	Sprite* Sprite::imageSprite(const char *filename){
		return ImageSprite::create(filename);
	}

	Sprite::Sprite(){
		_frames = 0;
		_duration = 0;
	}

	Vector3 Sprite::size() const{
		return _size;
	}
	
	float Sprite::width() const{
		return _size.x;
	}
	
	void Sprite::width(float w){
		_size.x = w;
	}
	
	float Sprite::height() const{
		return _size.y;
	}
	
	void Sprite::height(float h){
		_size.y = h;
	}

	
	int Sprite::frames() const{
		return _frames;
	}

	void Sprite::frames(int frames){
		_frames = frames;
	}

	float Sprite::duration() const{
		return _duration;
	}

	void Sprite::duration(float duration){
		_duration = duration;
	}

	
	GLuint Sprite::texture(){
		return textureAtFrame(0, NULL);
	}

	GLuint Sprite::textureAtTime(float time){
		return textureAtTime(time, NULL);
	}

	GLuint Sprite::textureAtFrame(int frame){
		return textureAtFrame(frame, NULL);
	}

}; // end namespace
