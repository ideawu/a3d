//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GLView.h"

@interface GLView(){
	NSTrackingArea *_trackingArea;
}
@end

// 显示效果为什么比SCNView差那么多？
@implementation GLView

+ (NSOpenGLPixelFormat*)defaultPixelFormat{
	NSOpenGLPixelFormatAttribute attrs[] = {
		NSOpenGLPFANoRecovery, // Enable automatic use of OpenGL "share" contexts.
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFADepthSize, 16,
//		NSOpenGLPFAAlphaSize, 8,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAAccelerated,
		0
	};
	NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
	return pixelFormat;
}

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format{
	self = [super initWithFrame:frameRect pixelFormat:format];
	[self setWantsBestResolutionOpenGLSurface:YES];
	//	CGSize ret = [self convertSizeToBacking:self.bounds.size];
	return self;
}

- (CGSize)viewportSize{
	return self.bounds.size;
}

- (CGSize)framebufferSize{
	return [self convertSizeToBacking:self.bounds.size];
}

- (void)prepareOpenGL{
	[super prepareOpenGL];
	
	//	glEnable(GL_MULTISAMPLE);
	//	glEnable(GL_LINE_SMOOTH);
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
}

- (void)drawRect:(NSRect)dirtyRect {
	[super drawRect:dirtyRect];
}

#pragma mark - Keyboard and Mouse event handle

- (BOOL)acceptsFirstResponder{
	return YES;
}

- (void)updateTrackingAreas{
	if(!_trackingArea){
		[self removeTrackingArea:_trackingArea];
	}
	NSTrackingAreaOptions options = (NSTrackingActiveAlways | NSTrackingInVisibleRect |
									 NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved);
	_trackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds]
												 options:options
												   owner:self
												userInfo:nil];
	[self addTrackingArea:_trackingArea];
}

@end

