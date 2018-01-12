//  Created by ideawu on 12/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GRay.h"

@implementation GRay

+ (GRay *)rayFrom:(GLKVector3)origin to:(GLKVector3)p{
	GRay *ret = [GRay new];
	ret.origin = origin;
	ret.direction = vec3_norm(vec3_sub(p, origin));
	return ret;
}

- (GLKVector3)nearestPointTo:(GLKVector3)target{
	GLKVector3 vec = vec3_sub(target, _origin);
	float dot = GLKVector3DotProduct(vec, _direction);
	if(dot < 0){
		return _origin;
	}
	GLKVector3 ret = vec3_norm(_direction);
	ret = GLKVector3MultiplyScalar(ret, fabs(dot));
	ret = vec3_add(ret, _origin);
	return ret;
}

@end
