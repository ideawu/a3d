//  Created by ideawu on 19/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_Rect_hpp
#define a3d_Rect_hpp

namespace a3d{
	class Frame
	{
	public:
		// width/height 可为负数
		float x, y, width, height;
		
		Frame();
		Frame(float x, float y, float width, float height);
		
		float top() const;
		float bottom() const;
		float left() const;
		float right() const;

		// origin point
		float x0() const;
		float y0() const;
		// diagon point
		float x1() const;
		float y1() const;

		bool equals(const Frame &d) const;
		bool empty() const;
		// 返回两者的交集区域
		Frame intersect(const Frame &d) const;
	};
}; // end namespace

#endif /* Rect_hpp */
