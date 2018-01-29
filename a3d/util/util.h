//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef util_h
#define util_h

#include <math.h>
#include <mach/mach_time.h>
#include <ImageIO/ImageIO.h>

namespace a3d{
	inline static double absolute_time(){
		return mach_absolute_time()/1000.0/1000.0/1000.0;
	}

	inline static float degree_to_radian(float degrees){
		return degrees * (M_PI / 180);
	}
	
	inline static float radian_to_degree(float radians){
		return radians * (180 / M_PI);
	}

	inline static float trimf(float f){
		return fabs(f)<FLT_EPSILON*10? 0 : f;
	}
	
	CGImageRef load_cgimage(const char *filename);
	char *load_image_data(const char *filename, int *width, int *height);

}; // end namespace

#endif /* util_h */
