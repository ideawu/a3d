//  Created by ideawu on 12/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#ifndef gmath_h
#define gmath_h

#import <Cocoa/Cocoa.h>
#import <GLKit/GLKit.h>

#define str_mat4		NSStringFromGLKMatrix4
#define str_vec3		NSStringFromGLKVector3
#define str_vec4		NSStringFromGLKVector4

#define mat4			GLKMatrix4MakeTranslation

#define mat4_mul_vec3	GLKMatrix4MultiplyVector3WithTranslation
#define mat4_mul_vec4	GLKMatrix4MultiplyVector4

#define mat4_mul		GLKMatrix4Multiply
#define mat4_mul_mat4	GLKMatrix4Multiply

#define mat4_invert(m)	GLKMatrix4Invert(m, NULL)

#define vec3			GLKVector3Make
#define vec3_norm		GLKVector3Normalize
#define vec3_add		GLKVector3Add
#define vec3_sub		GLKVector3Subtract

#define vec4			GLKVector4Make
#define vec4_add		GLKVector4Add
#define vec4_sub		GLKVector4Subtract


inline static float trimf(float f){
	return fabs(f)<FLT_EPSILON*10? 0 : f;
}

inline static float trimf_to(float f, float up){
	return fabs(f-up)<FLT_EPSILON*10? up : f;
}


#endif /* gmath_h */
