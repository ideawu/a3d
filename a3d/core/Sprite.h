//  Created by ideawu on 24/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_SpriteTexture_hpp
#define a3d_SpriteTexture_hpp

#include "Vector3.h"
#include "Texture.h"
#include "Bitmap.h"
#include "Color.h"

namespace a3d{
	class Sprite
	{
	public:
		static Sprite* emptySprite();
		static Sprite* imageSprite(const char *filename);
		static Sprite* bitmapSprite(const Bitmap &bitmap);
		static Sprite* textSprite(const char *str);
		static Sprite* textSprite(const char *str, float fontSize, const Color &fontColor);

		virtual ~Sprite(){}

		int frames() const;
		double duration() const;
		
		Vector3 size() const;
		float width() const;
		void width(float w);
		float height() const;
		void height(float h);

		// 如果无对应帧，返回NULL
		Texture* texture();
		Texture* textureAtTime(double time);
		Texture* textureAtFrame(int frame);
		
		// 如果指定时间无对应帧，返回-1
		virtual int frameAtTime(double time, double *duration) = 0;
		// 如果无对应帧，返回NULL
		virtual Texture* textureAtTime(double time, double *duration) = 0;
		virtual Texture* textureAtFrame(int frame, double *duration) = 0;

	protected:
		Sprite();

		int _frames;
		double _duration;
		
		void frames(int frames);
		void duration(double duration);

	private:
		Sprite(const Sprite &d);
		Sprite& operator =(const Sprite &d);

		Vector3 _size;
	};
}; // end namespace

#endif /* SpriteTexture_hpp */
