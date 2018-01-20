//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GLView.h"

@interface GLView(){
	NSTrackingArea *_trackingArea;
#if TARGET_OS_IPHONE
	CADisplayLink *_displayLink;
#else
	CVDisplayLinkRef _displayLink;
#endif
}
@property BOOL isOpenGLReady;
@end

@implementation GLView

+ (NSOpenGLPixelFormat*)defaultPixelFormat{
	NSOpenGLPixelFormatAttribute attrs[] = {
		NSOpenGLPFANoRecovery,
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFADepthSize, 16,
		NSOpenGLPFAAlphaSize, 8,
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
	_displayLink = NULL;
	return self;
}

- (void)dealloc{
	if(_displayLink){
		[self freeDisplayLink];
	}
}

- (void)prepareOpenGL{
	// 如果 OpenGL 没有 ready 就执行动画线程，会出错
	_isOpenGLReady = YES;
}

- (CGSize)viewportSize{
	return self.bounds.size;
}

- (CGSize)framebufferSize{
	return [self convertSizeToBacking:self.bounds.size];
}

- (void)drawRect:(NSRect)dirtyRect{
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


#pragma mark - DisplayLink

- (void)startAnimation{
	if(!_displayLink){
		[self setupDisplayLink];
	}
	if(_displayLink && !CVDisplayLinkIsRunning(_displayLink)){
		[self startDisplayLink];
	}
}

- (void)stopAnimation{
	if(_displayLink && CVDisplayLinkIsRunning(_displayLink)){
		[self stopDisplayLink];
	}
}

- (BOOL)isAnimating{
	return _displayLink && CVDisplayLinkIsRunning(_displayLink);
}

- (BOOL)renderAtTime:(double)time{
	return YES;
}


- (void)setupDisplayLink{
#if TARGET_OS_IPHONE
	_displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(displayLinkCallback:)];
	[_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
	[_displayLink setPaused:YES];
#else
	CVReturn ret;
	ret = CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);
	ret = CVDisplayLinkSetOutputCallback(_displayLink, displayLinkCallback, (__bridge void *)(self));
#endif
}

- (void)freeDisplayLink{
	[self stopDisplayLink];
	CVDisplayLinkRelease(_displayLink);
	_displayLink = NULL;
}

- (void)startDisplayLink{
#if TARGET_OS_IPHONE
	[_displayLink setPaused:NO];
#else
	CVDisplayLinkStart(_displayLink);
#endif
}

- (void)stopDisplayLink{
#if TARGET_OS_IPHONE
	[_displayLink setPaused:YES];
#else
	CVDisplayLinkStop(_displayLink);
#endif
}

#if TARGET_OS_IPHONE
- (void)displayLinkCallback:(CADisplayLink *)sender{
	double time = _displayLink.timestamp;
	[self renderAtTime:time];
}
#else
static CVReturn displayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *now,
									const CVTimeStamp *outputTime, CVOptionFlags flagsIn,
									CVOptionFlags *flagsOut, void *displayLinkContext){
	double time = outputTime->hostTime/1000.0/1000.0/1000.0;
	GLView *view = (__bridge GLView *)displayLinkContext;
	if(view.isOpenGLReady){
		BOOL ret = [view renderAtTime:time];
		return ret? kCVReturnSuccess : kCVReturnError;
	}else{
		return kCVReturnSuccess;
	}
}
#endif

@end

