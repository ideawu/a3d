//  Created by ideawu on 19/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Frame.h"
#include <CoreGraphics/CGGeometry.h>

namespace a3d{
	
	Frame::Frame(){
		x = y = width = height = 0;
	}
	
	Frame::Frame(float x, float y, float width, float height){
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	float Frame::top() const{
		return y;
	}
	
	float Frame::bottom() const{
		return y + height;
	}
	
	float Frame::left() const{
		return x;
	}
	
	float Frame::right() const{
		return x + width;
	}

	float Frame::x0() const{
		return left();
	}
	
	float Frame::y0() const{
		return top();
	}
	
	float Frame::x1() const{
		return right();
	}
	
	float Frame::y1() const{
		return bottom();
	}

	bool Frame::equals(const Frame &d) const{
		return x == d.x && y == d.y && width == d.width && height == d.height;
	}

	bool Frame::empty() const{
		return width == 0 || height == 0;
	}

	Frame Frame::intersect(const Frame &d) const{
		CGRect r1 = CGRectMake(x, y, width, height);
		CGRect r2 = CGRectMake(d.x, d.y, d.width, d.height);
		CGRect r = CGRectIntersection(r1, r2);
		if(CGRectIsNull(r)){
			return Frame();
		}
		return Frame(r.origin.x, r.origin.y, r.size.width, r.size.height);
	}

}; // end namespace
