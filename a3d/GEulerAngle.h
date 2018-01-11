//  Created by ideawu on 07/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GMatrix4.h"

@interface GEulerAngle : NSObject

@property (readonly) GLKMatrix4 matrix;

@property float roll;
@property float pitch;
@property float yaw;

+ (GEulerAngle *)angleWithMatrix:(GMatrix4 *)matrix;
+ (GEulerAngle *)angleWithMatrix:(GMatrix4 *)matrix mode:(const char *)mode;

- (id)initWithMatrix:(GMatrix4 *)matrix;
- (id)initWithMatrix:(GMatrix4 *)matrix mode:(const char *)mode;

- (void)reset;
- (void)parseMatrix:(GMatrix4 *)matrix;

- (void)subtract:(GEulerAngle *)right;

@end
