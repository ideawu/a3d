//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>

// 注意！在进行OpenGL资源创建时，如glGenTextures()，要先[self.openGLContext makeCurrentContext];
// https://stackoverflow.com/questions/7610117/layer-backed-openglview-redraws-only-if-window-is-resized/11213382

@interface A3DView : NSView

+ (NSOpenGLPixelFormat*)defaultPixelFormat;
+ (NSOpenGLContext*)defaultOpenGLContext;

@property (readonly) NSOpenGLContext *openGLContext;
@property (readonly) NSOpenGLPixelFormat *pixelFormat;

@property (readonly) CGSize viewportSize;
@property (readonly) CGSize framebufferSize;
@property (readonly) float fps;

// 子类可重写此方法。OpenGL 初始化时，系统调用此方法。
- (void)setup;
// 子类可重写此方法。OpenGL 销毁时，系统调用此方法。
- (void)clean;
// 子类可重写此方法。
- (void)reshape;
// 子类可重写此方法。在此方法中渲染。基于性能考虑，不要在此方法中调用 glFlush/glFinish
- (void)renderAtTime:(double)time;
//- (void)drawRect:(NSRect)dirtyRect;

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


- (void)showStatistics;
- (void)hideStatistics;

@end
