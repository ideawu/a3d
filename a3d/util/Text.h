//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Text_hpp
#define a3d_Text_hpp

#include <string>
#include "Bitmap.h"
#include "Color.h"

namespace a3d{
	class Text
	{
	public:
		Text();
		Text(const char *text);
		~Text();
		
		void maxWidth(int maxWidth);
		void maxHeight(int maxHeight);
		void font(const char *name, float size);
		void fontSize(float size);
		void fontColor(const Color &color);
		void text(const char *text);
		
		void calculateSize(int *width, int *height);
		Bitmap* drawToBitmap();

	private:
		Text(const Text &d);
		Text& operator =(const Text &d);
		
		int _maxWidth;
		int _maxHeight;
		std::string _fontName;
		float _fontSize;
		Color _fontColor;
		
		std::string _text;

		void* createAttributedString();
	};
}; // end namespace

#endif /* Text_hpp */
