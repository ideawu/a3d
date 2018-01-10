//  Created by ideawu on 07/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GMatrix4.h"

@interface EulerAngle : NSObject

@property float roll;
@property float pitch;
@property float yaw;

+ (EulerAngle *)angleOfMatrix:(GMatrix4 *)matrix;

- (id)initWithMatrix:(GMatrix4 *)matrix;

- (void)reset;
- (void)parseMatrix:(GMatrix4 *)matrix;

@end
