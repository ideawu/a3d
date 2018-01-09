
#import <Foundation/Foundation.h>
#import "GMatrix4.h"

static float angle(GLKVector3 axis){
	axis = GLKVector3Normalize(axis);
	
	// x pitch
//	GLKVector3 u = GLKVector3Make(axis.x, axis.y, 0); // 在XY平面上的投影向量
//	GLKVector3 v = GLKVector3Make(0, 0, 1); // 平面垂直方向的向量
	// y yaw
	GLKVector3 u = GLKVector3Make(0, axis.y, axis.z); // 在YZ平面上的投影向量
	GLKVector3 v = GLKVector3Make(1, 0, 0); // 平面垂直方向的向量
	// z roll
//	GLKVector3 u = GLKVector3Make(axis.x, 0, axis.z); // 在ZX平面上的投影向量
//	GLKVector3 v = GLKVector3Make(0, 1, 0); // 平面垂直方向的向量
	
	u = GLKVector3Normalize(u);
	v = GLKVector3Normalize(v);

	GLKVector3 orig = GLKVector3CrossProduct(u, v); // 平面上与轴垂直的向量
	log_debug(@"%@", NSStringFromGLKVector3(u));
	log_debug(@"%@", NSStringFromGLKVector3(v));
	log_debug(@"orig %@", NSStringFromGLKVector3(orig));
	GLKVector3 vec = GLKVector3Make(axis.x, axis.y - orig.y, axis.z - orig.z);
	vec = GLKVector3Normalize(vec);
	float angle = atan2(vec.z, vec.x);
	return GLKMathRadiansToDegrees(angle);
}

int main(int argc, const char * argv[]) {
	GMatrix4 *mat = [GMatrix4 make];
	log_debug(@"%@", mat);
	[mat moveX:10 y:10 z:10];
	log_debug(@"%@", mat);
	[mat rotateX:45];
	log_debug(@"%@", mat);
	[mat moveX:1 y:0 z:0];
	log_debug(@"\n%@", mat);
	log_debug(@"%.2f %.2f %.2f", mat.xAngle, mat.yAngle, mat.zAngle);
	[mat resetRotation];
	log_debug(@"%@", mat);
	
	{
		log_debug(@"%.2f", angle(GLKVector3Make(0, 1, 0)));
//		log_debug(@"%.2f", angle(GLKVector3Make(0, 0, -1)));
//		log_debug(@"%.2f", angle(GLKVector3Make(1, 1, 1)));
//		log_debug(@"%.2f", angle(GLKVector3Make(-1, -0.001, 0)));
//		log_debug(@"%.2f", angle(GLKVector3Make(0, 0, 1)));
	}
	return 0;
}
