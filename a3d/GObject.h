//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <GLKit/GLKit.h>
#import "GMatrix4.h"
#import "GEulerAngle.h"

@interface GObject : GMatrix4

// 视线角度
@property GEulerAngle *angle;

// 物体在父坐标系中的体积
@property float width;
@property float height;
@property float depth;

- (GObject *)clone;
- (void)copy:(GObject *)src;

- (void)scale:(float)ratio;


@end
