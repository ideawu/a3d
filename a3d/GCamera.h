//  Created by ideawu on 31/12/2017.
//  Copyright © 2017 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>
#import <GLKit/GLKit.h>
#import "GObject.h"

@interface GCamera : GObject

// 竖直方向的视角
@property float fovy;
// 视觉的焦点坐标
@property GLKVector3 lookAt;

- (void)lookAtX:(float)x y:(float)y z:(float)z;

@end
