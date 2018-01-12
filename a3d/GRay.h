//  Created by ideawu on 12/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <GLKit/GLKit.h>
#import "gmath.h"

// 射线是带有方向的直线
@interface GRay : NSObject

@property GLKVector3 origin;
@property GLKVector3 direction;

+ (GRay *)rayFrom:(GLKVector3)origin to:(GLKVector3)p;

- (GLKVector3)nearestPointTo:(GLKVector3)target;

@end
