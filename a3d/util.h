//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef util_h
#define util_h

#include <ImageIO/CGImageSource.h>

namespace a3d{
}; // end namespace

namespace a3d{
	inline static float trimf(float f){
		return fabs(f)<FLT_EPSILON*10? 0 : f;
	}
	
	CGImageRef load_cgimage(const char *filename);
	char *load_image_data(const char *filename, int *width, int *height);

}; // end namespace

#endif /* util_h */
