//  Created by ideawu on 02/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

int main(int argc, const char * argv[]) {
	GLKMatrix4 mat = GLKMatrix4Identity;
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(181+100));
	GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(mat);
	GLKVector3 axis = GLKQuaternionAxis(quat);
	float angle = GLKQuaternionAngle(quat);
	log_debug(@"%.2f %.2f %.2f %.2f", axis.x, axis.y, axis.z, GLKMathRadiansToDegrees(angle));
	return 0;
}
