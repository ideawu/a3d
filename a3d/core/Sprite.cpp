//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Sprite.h"
#include "ImageSprite.h"
#include "TextSpirte.h"

namespace a3d{

	Sprite* Sprite::imageSprite(const char *filename){
		return ImageSprite::createFromFile(filename);
	}

	Sprite* Sprite::imageSprite(const Bitmap &bitmap){
		return ImageSprite::createFromBitmap(bitmap);
	}

	Sprite* Sprite::textSprite(const char *str){
		return TextSprite::create(str);
	}

	Sprite* Sprite::textSprite(const char *str, float fontSize, const Color &fontColor){
		return TextSprite::create(str, fontSize, fontColor);
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

	double Sprite::duration() const{
		return _duration;
	}

	void Sprite::duration(double duration){
		_duration = duration;
	}

	Texture* Sprite::texture(){
		return textureAtFrame(0, NULL);
	}

	Texture* Sprite::textureAtTime(double time){
		return textureAtTime(time, NULL);
	}

	Texture* Sprite::textureAtFrame(int frame){
		return textureAtFrame(frame, NULL);
	}

	int Sprite::frameAtTime(double time, double *duration){
		return -1;
	}
	
	Texture* Sprite::textureAtTime(double time, double *duration){
		return NULL;
	}
	
	Texture* Sprite::textureAtFrame(int frame, double *duration){
		return NULL;
	}

}; // end namespace
