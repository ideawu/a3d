//  Created by ideawu on 18/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Transform.h"
#include "Object.h"

namespace a3d{

	Transform Transform::transformBetween(const Object &first, const Object &second){
		Transform ret;

		// opacity 变动
		ret.opacity = second.opacity() - first.opacity();
		
		// size 变动
		Vector3 size1 = first.size();
		Vector3 size2 = second.size();
		ret.size = size2.sub(size1);
		
		// matrix 变动
		Matrix4 mat1 = first.matrix();
		Matrix4 mat2 = second.matrix();
		ret.matrix = mat2.div(mat1);

//		Vector3 p = mat2.position().sub(mat1.position());
//		Vector3 s = mat2.scale().sub(mat1.scale()).add(Vector3(1, 1, 1));
//		Vector3 r = mat2.rotation().sub(mat1.rotation());
//
//		Matrix4 mat;
//		mat.rotate(r);
//		mat.translate(p);
//		mat.scale(s);
//		ret.matrix = mat;

//		if(fabs(ret.matrix.x()) > 1 || fabs(ret.matrix.y()) > 1){
//			log_debug("x: %f %f %f  y: %f %f %f", mat1.x(), mat2.x(), ret.matrix.x(), mat1.y(), mat2.y(), ret.matrix.y());
//			log_debug("mat1 \n%s", mat1.str().c_str());
//			log_debug("mat2 \n%s", mat2.str().c_str());
//			log_debug("mat1.invert\n%s", mat1.invert().str().c_str());
//			Point3 p = Point3(mat1.x(), mat1.y(), mat1.z());
//			log_debug("%f", mat1.invert().mul(p).x);
//			log_debug("trans \n%s", ret.matrix.str().c_str());
//		}

		return ret;
	}
}; // end namespace

