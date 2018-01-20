//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GLView : NSOpenGLView

@property (readonly) CGSize viewportSize;
@property (readonly) CGSize framebufferSize;

- (void)drawRect:(NSRect)dirtyRect;
// TODO: 如果无法渲染指定时间帧，且希望重新渲染，返回NO
- (BOOL)renderAtTime:(double)time;

// 激活 renderAtTime: 的调用
- (void)startAnimation;
// 停止 renderAtTime: 的调用
- (void)stopAnimation;
// 判断 renderAtTime: 的调用是否已被激活 
- (BOOL)isAnimating;

@end
