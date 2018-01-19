//  Created by ideawu on 19/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef Rect_hpp
#define Rect_hpp

namespace a3d{
	class Rect
	{
	public:
		float x, y, width, height;
		
		Rect();
		Rect(float x, float y, float width, float height);
	};
}; // end namespace

#endif /* Rect_hpp */
