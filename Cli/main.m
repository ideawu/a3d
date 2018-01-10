
#import <Foundation/Foundation.h>
#import "GMatrix4.h"
#import "EulerAngle.h"

int main(int argc, const char * argv[]) {
	GMatrix4 *mat = [GMatrix4 make];

//	[mat rotateY:45];
//	[mat rotateX:45];

	for(int i=0; i<8; i++){
		[mat rotateZ:45];
		log_debug(@"%@", [EulerAngle angleOfMatrix:mat]);
	}
	log_debug(@"");

	for(int i=0; i<8; i++){
		[mat rotateX:45];
		log_debug(@"%@", [EulerAngle angleOfMatrix:mat]);
	}
	log_debug(@"");

	for(int i=0; i<8; i++){
		[mat rotateY:45];
		log_debug(@"%@", [EulerAngle angleOfMatrix:mat]);
	}
	log_debug(@"");

//	log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
//	[mat rotateZ:90];
//	log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
//	[mat rotateX:-1];
//	log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
//	[mat rotateX:+2];
//	log_debug(@"roll: %.2f, pitch: %.2f, yaw: %.2f", mat.rollAngle, mat.pitchAngle, mat.yawAngle);
//	log_debug(@"");


	return 0;
}
