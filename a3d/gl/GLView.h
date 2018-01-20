//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GLView : NSOpenGLView

@property (readonly) CGSize viewportSize;
@property (readonly) CGSize framebufferSize;

// 如果子类同时重写 drawRect: 和 renderAtTime:，要注意两者在不同的线程中，需要 lock NSOpenGLContext。
- (void)drawRect:(NSRect)dirtyRect;
// 注意：在独立的线程中执行渲染。子类重写此方法，如果渲染成功，返回YES，如果渲染失败且希望再次渲染该时间对应的帧，返回NO。
- (BOOL)renderAtTime:(double)time;

// 激活 renderAtTime: 的调用
- (void)startAnimation;
// 停止 renderAtTime: 的调用
- (void)stopAnimation;
// 判断 renderAtTime: 的调用是否已被激活 
- (BOOL)isAnimating;

@end
