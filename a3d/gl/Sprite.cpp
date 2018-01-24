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

	Vector3 Sprite::size() const{
		return Vector3(_width, _height, 0);
	}

	int Sprite::width() const{
		return _width;
	}

	void Sprite::width(int w){
		_width = w;
	}

	int Sprite::height() const{
		return _height;
	}

	void Sprite::height(int h){
		_height = h;
	}

	GLuint Sprite::texture(){
		return textureAtFrame(0, NULL);
	}

	GLuint Sprite::textureAtFrame(int frame){
		return textureAtFrame(frame, NULL);
	}

	GLuint Sprite::textureAtTime(float time){
		return textureAtTime(time, NULL);
	}
	
}; // end namespace
