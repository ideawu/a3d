//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>
#import <GLKit/GLKit.h>
#import "GObject.h"

// 对相机坐标系做变换，相当于对世界坐标系做相反的变换
@interface GCamera : GObject

// 竖直方向的视角
@property float fovy;
// 视觉的焦点坐标
@property GLKVector3 lookAt;

- (void)lookAtX:(float)x y:(float)y z:(float)z;

@end
