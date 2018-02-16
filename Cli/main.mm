//  Created by ideawu on 02/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "a3d.h"

using namespace a3d;

int main(int argc, const char * argv[])
{
	Matrix4 origin, target, current;

	// origin
	origin.translate(100, 100, 100);
	origin.rotateY(45);
	log_debug("origin:\n%s", origin.str().c_str());

	{
		// animate target
		target = origin;
		target.rotateX(30);

		// sync current
		current = target;
		log_debug("current & target:\n%s", current.str().c_str());
	}

	// manually transform target
	target.rotateX(10);


	// q0, q1
	// rotateTo(q1).rotate(q0.invert())
	{
		Matrix4 mat;
		mat.rotateY(45);
		Quaternion q1 = mat.quaternion();
		log_debug(@"%.2f %s", q1.angle(), q1.vector().str().c_str());
		mat.rotateX(45);
		Quaternion q2 = mat.quaternion();
		log_debug(@"%.2f %s", q2.angle(), q2.vector().str().c_str());

		Quaternion q3 = q2.div(q1);
		log_debug(@"%.2f %s", q3.angle(), q3.vector().str().c_str());
		q3 = q1.mul(q3);
		log_debug(@"%.2f %s", q3.angle(), q3.vector().str().c_str());
	}

	{
		Matrix4 mat1, mat2;

		mat1.rotateY(45);

		mat2.rotateY(45);
		mat2.rotateX(45);

		log_debug("mat2:\n%s", mat2.str().c_str());
//		log_debug("mat1:\n%s", mat1.str().c_str());

		Matrix4 df = mat2.div(mat1);
		Quaternion q2 = df.quaternion();
		log_debug(@"%.2f %s", q2.angle(), q2.vector().str().c_str());

		Matrix4 mat = df.mul(mat1);
		log_debug("(mat2/mat1) * mat1=:\n%s", mat.str().c_str());

	}

	return 0;
}

