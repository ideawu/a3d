//  Created by ideawu on 19/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Rect_hpp
#define Rect_hpp

namespace a3d{
	class Frame
	{
	public:
		float x, y, width, height;
		
		Frame();
		Frame(float x, float y, float width, float height);
		
		float centerX() const{return x+width/2;}
		float centerY() const{return y+height/2;}

		bool equals(const Frame &d) const;
		// 返回两者的交集区域
		Frame intersection(const Frame &d) const;
	};
}; // end namespace

#endif /* Rect_hpp */
