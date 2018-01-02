//  Created by ideawu on 28/12/2017.
//  Copyright © 2017 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>
#import <GLKit/GLKit.h>
#import "GNode.h"
#import "GCamera.h"

@interface GWorld : NSObject

@property (readonly) GCamera *camera;

- (void)enableOffscreenBuffer;
- (void)disableOffscreenBuffer;

// 输入参数会被自动转成整数，如果不是偶数，加1变成偶数。
- (void)setCameraWidth:(float)width height:(float)height;

/*
 一般是如下调用顺序，此顺序不能改变：
 beginRender
 render3D
 // custom 3D rendering
 render2D
 // custom 2D rendering
 */
- (void)beginRender;
- (void)render3D;
- (void)render2D;
- (void)finishRender;

- (void)addNode:(GNode *)node;

@end
