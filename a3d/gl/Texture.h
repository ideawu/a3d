//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Texture_hpp
#define a3d_Texture_hpp

#include "Bitmap.h"
#include "Frame.h"
#include "Vector3.h"

namespace a3d{
	/// VRAM based image
	class Texture
	{
	public:
		~Texture();

		static Texture* create(int width, int height);
		static Texture* createFromBitmap(const Bitmap *bitmap);

		Vector3 size() const;
		float width() const;
		float height() const;

		GLuint name() const;
		void bind() const;
		void unbind() const;
		void loadBitmap(const Bitmap *bitmap);
		
		void draw(const Frame &texRect, const Frame verRect) const;
		
		// TODO: retain, release
		
	private:
		Texture();
		Texture(const Texture &d);
		Texture& operator =(const Texture &d);

		GLuint _tid;
		Vector3 _size;

		static int texture_count;
	};
}; // end namespace

#endif /* Texture_hpp */
