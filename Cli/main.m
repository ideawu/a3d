
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
//	[mat rotateY:45];
//	[mat rotateX:45];
	for(int i=0; i<8; i++){
		[mat rotateX:45];
		log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
	}
	log_debug(@"");
	for(int i=0; i<8; i++){
		[mat rotateY:45];
		log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
	}
	log_debug(@"");
	for(int i=0; i<8; i++){
		[mat rotateZ:45];
		log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
	}
	log_debug(@"");
//	log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
//	[mat rotateX:45];
//	log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
//	[mat rotateY:45];

//	[mat resetRoll];
//	log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
//	[mat resetPitch];
//	log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
//	[mat resetYaw];
//	log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);

	return 0;
}
