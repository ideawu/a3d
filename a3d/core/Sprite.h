//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef SpriteTexture_hpp
#define SpriteTexture_hpp

#include "Node.h"

namespace a3d{
	class Sprite : public Node
	{
	public:
		static Sprite* imageSprite(const char *filename);
		
		virtual ~Sprite(){}

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
