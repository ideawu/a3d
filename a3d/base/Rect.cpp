//  Created by ideawu on 19/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Rect.h"
#include <CoreGraphics/CGGeometry.h>

namespace a3d{
	
	Rect::Rect(){
		x = y = width = height = 0;
	}
	
	Rect::Rect(float x, float y, float width, float height){
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	float Rect::x0() const{
		return x;
	}
	
	float Rect::y0() const{
		return y;
	}
	
	float Rect::x1() const{
		return x + width;
	}
	
	float Rect::y1() const{
		return y + height;
	}

	bool Rect::equals(const Rect &d) const{
		return x == d.x && y == d.y && width == d.width && height == d.height;
	}

	bool Rect::empty() const{
		return width == 0 || height == 0;
	}

	Rect Rect::intersect(const Rect &d) const{
		CGRect r1 = CGRectMake(x, y, width, height);
		CGRect r2 = CGRectMake(d.x, d.y, d.width, d.height);
		CGRect r = CGRectIntersection(r1, r2);
		if(CGRectIsNull(r)){
			return Rect();
		}
		return Rect(r.origin.x, r.origin.y, r.size.width, r.size.height);
	}

}; // end namespace
