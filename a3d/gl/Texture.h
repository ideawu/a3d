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
		static Texture* textureFromImageFile(const char *filename);
		
		GLuint id() const;
		int width() const;
		void width(int w);
		int height() const;
		void height(int h);

	private:
		Texture(const Texture &d);
		Texture& operator =(const Texture& d);

		GLuint _id;
		int _width;
		int _height;

		void id(GLuint i);
		int loadImageFile(const char *filename);
};
}; // end namespace

#endif /* Texture_hpp */
