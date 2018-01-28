//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef SpriteTexture_hpp
#define SpriteTexture_hpp

#include "Vector3.h"

namespace a3d{
	class Sprite
	{
	public:
		static Sprite* imageSprite(const char *filename);
		
		virtual ~Sprite(){}

		int frames() const;
		float duration() const;
		Vector3 size() const;
		float width() const;
		float height() const;

		GLuint texture();
		// 如果无对应帧，返回0
		GLuint textureAtTime(float time);
		GLuint textureAtFrame(int frame);
		// 如果指定时间无对应帧，返回-1
		virtual int frameAtTime(float time, float *duration) = 0;
		// 如果无对应帧，返回0
		virtual GLuint textureAtTime(float time, float *duration) = 0;
		virtual GLuint textureAtFrame(int frame, float *duration) = 0;

	protected:
		Sprite();

		int _frames;
		float _duration;
		
		void width(float w);
		void height(float h);
		void frames(int frames);
		void duration(float duration);

	private:
		Sprite(const Sprite &d);
		Sprite& operator =(const Sprite &d);

		Vector3 _size;
	};
}; // end namespace

#endif /* SpriteTexture_hpp */
