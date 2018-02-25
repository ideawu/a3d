//  Created by ideawu on 18-2-25.
//  Copyright (c) 2018年 ideawu. All rights reserved.
//

#import "A3DLayer.h"

@implementation A3DLayer

- (void)drawInOpenGLContext:(NSOpenGLContext *)context pixelFormat:(NSOpenGLPixelFormat *)pixelFormat forLayerTime:(CFTimeInterval)t displayTime:(const CVTimeStamp *)ts{
	log_debug(@"%s %@ %@", __func__, context, self.openGLContext);
	[self.view drawRect:self.view.bounds];
}

- (NSOpenGLPixelFormat *)openGLPixelFormatForDisplayMask:(uint32_t)mask{
	log_debug(@"%d %@", mask, self.openGLPixelFormat);
	return self.openGLPixelFormat;
}

- (NSOpenGLContext *)openGLContextForPixelFormat:(NSOpenGLPixelFormat *)pixelFormat{
	log_debug(@"%@", pixelFormat);
	return self.openGLContext;
}

@end
