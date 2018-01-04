//  Created by ideawu on 28/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <GLKit/GLKit.h>
#import "GNode.h"
#import "GCamera.h"

@interface GWorld : NSObject

@property float width;
@property float height;
@property float depth;

@property (readonly) GCamera *camera;

- (void)enableOffscreenBuffer;
- (void)disableOffscreenBuffer;

// 输入width,height参数会被自动转成整数，如果不是偶数，加1变成偶数。
- (void)setCameraWidth:(float)width height:(float)height depth:(float)depth;
- (void)setCameraFovy:(float)fovy width:(float)width height:(float)height depth:(float)depth;

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
