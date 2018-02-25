//  Created by ideawu on 18-2-25.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#import "A3DLayer.h"

@interface A3DLayer()
@end

@implementation A3DLayer

- (BOOL)canDrawInOpenGLContext:(NSOpenGLContext *)context pixelFormat:(NSOpenGLPixelFormat *)pixelFormat forLayerTime:(CFTimeInterval)t displayTime:(const CVTimeStamp *)ts{
	return self.canDraw;
//	return YES;
}

- (void)drawInOpenGLContext:(NSOpenGLContext *)context pixelFormat:(NSOpenGLPixelFormat *)pixelFormat forLayerTime:(CFTimeInterval)t displayTime:(const CVTimeStamp *)ts{
//	[super drawInOpenGLContext:context pixelFormat:pixelFormat forLayerTime:t displayTime:ts];
//	log_debug(@"%@ %@", context, self.openGLContext);
	[self.view drawRect:self.view.bounds];
	self.canDraw = NO;
	// 多线程渲染实现逻辑：
	// 0. setAsynchronous:YES
	// 1. 在其它线程渲染OpenGL到纹理，完毕后canDrawInOpenGLContext返回YES
	// 2. 在drawInOpenGLContext把纹理画到当前context
}

- (NSOpenGLPixelFormat *)openGLPixelFormatForDisplayMask:(uint32_t)mask{
//	log_debug(@"%d %@", mask, self.openGLPixelFormat);
	return self.openGLPixelFormat;
}

- (NSOpenGLContext *)openGLContextForPixelFormat:(NSOpenGLPixelFormat *)pixelFormat{
//	log_debug(@"%@", pixelFormat);
	return self.openGLContext;
}

@end
