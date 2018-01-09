
#import <Foundation/Foundation.h>
#import "GMatrix4.h"

static float angle(GLKVector3 vec0, GLKVector3 vec1){
	GLKVector3 direction = GLKVector3Make(0, 0, 1);
	GLKVector3 cross = GLKVector3CrossProduct(vec0, vec1); // 旋转轴
	float sign = GLKVector3DotProduct(direction, cross); // 旋转轴在方向轴上的投影
	float dot = GLKVector3DotProduct(vec0, vec1);
	float angle = atan2(copysign(GLKVector3Length(cross), sign), dot);
	return GLKMathRadiansToDegrees(angle);
}

int main(int argc, const char * argv[]) {
	GMatrix4 *mat = [GMatrix4 make];
	log_debug(@"%@", mat);
	[mat rotateZ:45];
	log_debug(@"xroll: %.2f, yroll: %.2f, zroll: %.2f", mat.xRoll, mat.yRoll, mat.zRoll);
	
	return 0;
}
