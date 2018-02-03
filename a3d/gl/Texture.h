//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "Bitmap.h"
#include "Rect.h"

namespace a3d{
	class Texture
	{
	public:
		Texture();
		~Texture();

		static Texture* createFromBitmap(const Bitmap &bitmap);
		
		GLuint name() const;
		void bind();
		void unbind();
		void loadBitmap(const Bitmap &bitmap);
		
		void draw(const Rect &texRect, const Rect vertRect);
		
	private:
		Texture(const Texture &d);
		Texture& operator =(const Texture &d);

		GLuint _tid;
	};
}; // end namespace

#endif /* Texture_hpp */
