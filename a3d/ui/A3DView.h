//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>

// TODO: 显示 statistics
// 注意！在进行OpenGL资源创建时，如glGenTextures()，要先[self.openGLContext makeCurrentContext];

@interface A3DView : NSOpenGLView

@property (readonly) CGSize viewportSize;
@property (readonly) CGSize framebufferSize;
@property (readonly) float fps;

- (void)drawRect:(NSRect)dirtyRect;
- (void)renderAtTime:(double)time;

// 激活 renderAtTime: 的调用
- (void)startAnimation;
// 停止 renderAtTime: 的调用
- (void)stopAnimation;
- (void)toggleAnimation;
// 判断 renderAtTime: 的调用是否已被激活 
- (BOOL)isAnimating;

// 限制刷新率，性能相关，必须大于0。注意，设置此值小于100，可能使动画不流畅。
- (void)setMaxFPS:(float)fps;
// 默认为1，按正常时钟速度，指定为0.5则变慢
- (void)setTimescale:(double)scale;

@end
