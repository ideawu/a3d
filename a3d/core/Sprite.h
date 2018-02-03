//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef SpriteTexture_hpp
#define SpriteTexture_hpp

#include "Vector3.h"
#include "Texture.h"

namespace a3d{
	class Texture;
	
	class Sprite
	{
	public:
		static Sprite* imageSprite(const char *filename);
		static Sprite* textSprite(const char *str);

		virtual ~Sprite(){}

		int frames() const;
		double duration() const;
		Vector3 size() const;
		float width() const;
		float height() const;

		Texture* texture();
		// 如果无对应帧，返回NULL
		Texture* textureAtTime(double time);
		Texture* textureAtFrame(int frame);
		// 如果指定时间无对应帧，返回-1
		virtual int frameAtTime(double time, double *duration) = 0;
		// 如果无对应帧，返回0
		virtual Texture* textureAtTime(double time, double *duration) = 0;
		virtual Texture* textureAtFrame(int frame, double *duration) = 0;

	protected:
		Sprite();

		int _frames;
		double _duration;
		
		void width(float w);
		void height(float h);
		void frames(int frames);
		void duration(double duration);

	private:
		Sprite(const Sprite &d);
		Sprite& operator =(const Sprite &d);

		Vector3 _size;
	};
}; // end namespace

#endif /* SpriteTexture_hpp */
