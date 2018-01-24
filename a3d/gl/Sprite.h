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

		GLuint id() const;
		Vector3 size() const;
		int width() const;
		void width(int w);
		int height() const;
		void height(int h);

		int frames() const;
		float duration() const;

		GLuint texture();
		GLuint textureAtFrame(int frame);
		GLuint textureAtTime(float time);
		virtual GLuint textureAtFrame(int frame, float *duration) = 0;
		virtual GLuint textureAtTime(float time, float *duration) = 0;

	protected:
		Sprite();

		int _frames;
		float _duration;
		
		void frames(int frames);
		void duration(float duration);

	private:
		Sprite(const Sprite &d);
		Sprite& operator =(const Sprite& d);

		int _width;
		int _height;
	};
}; // end namespace

#endif /* SpriteTexture_hpp */
