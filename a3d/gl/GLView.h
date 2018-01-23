//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GLView : NSOpenGLView

@property (readonly) CGSize viewportSize;
@property (readonly) CGSize framebufferSize;

- (void)drawRect:(NSRect)dirtyRect;
- (void)renderAtTime:(double)time;

// 激活 renderAtTime: 的调用
- (void)startAnimation;
// 停止 renderAtTime: 的调用
- (void)stopAnimation;
// 判断 renderAtTime: 的调用是否已被激活 
- (BOOL)isAnimating;

// 调试用，限制刷新率
- (void)setMaxFPS:(float)fps;
// 默认为1，按正常时钟速度，指定为0.5则变慢
- (void)setTimescale:(float)scale;

@end
