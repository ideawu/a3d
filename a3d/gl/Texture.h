//  Created by ideawu on 17/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

namespace a3d{
	class Texture
	{
	public:
		Texture();
		~Texture();
		
		GLuint id() const;
		void id(GLuint i);
		int width() const;
		void width(int w);
		int height() const;
		void height(int h);

		int loadImageFile(const char *filename);
	private:
		Texture(const Texture &tex){}
		GLuint _id;
		int _width;
		int _height;
	};
}; // end namespace

#endif /* Texture_hpp */
