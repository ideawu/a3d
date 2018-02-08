//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef a3d_util_h
#define a3d_util_h

#include <math.h>
#include <mach/mach_time.h>

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
		return fabs(f)<__FLT_EPSILON__*10? 0 : f;
	}

}; // end namespace

#endif /* util_h */
