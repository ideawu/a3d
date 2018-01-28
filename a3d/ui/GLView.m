//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GLView.h"
#include <mach/mach_time.h>

@interface GLView(){
	NSTrackingArea *_trackingArea;
#if TARGET_OS_IPHONE
	CADisplayLink *_displayLink;
#else
	CVDisplayLinkRef _displayLink;
#endif
	dispatch_queue_t _processQueue;
	float _timescale;
	float _limitRefreshInterval;
	BOOL _isOpenGLReady;
	NSMutableArray *_jobs;
}
// renderTime = second - first
@property double firstRenderTick;
@property double secondRenderTick;
@property double pauseRenderTick;
@property BOOL isRendering;
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
	_processQueue = NULL;
	_timescale = 1.0;
	_limitRefreshInterval = 0;
	_isOpenGLReady = NO;
	_jobs = [[NSMutableArray alloc] init];
	return self;
}

- (void)dealloc{
	if(_displayLink){
		[self freeDisplayLink];
	}
}

- (void)prepareOpenGL{
	// 如果 OpenGL 没有 ready 就执行动画线程，会出错
	[self setIsOpenGLReady:YES];
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
		_pauseRenderTick = _secondRenderTick;
	}
}

- (BOOL)isAnimating{
	return _displayLink && CVDisplayLinkIsRunning(_displayLink);
}

- (void)renderAtTime:(double)time{
}


- (void)setupDisplayLink{
//	_processQueue = dispatch_queue_create("GLView_queue", DISPATCH_QUEUE_SERIAL);
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
	[self invokeRender:time];
}
#else
static CVReturn displayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *now,
									const CVTimeStamp *outputTime, CVOptionFlags flagsIn,
									CVOptionFlags *flagsOut, void *displayLinkContext){
//	log_debug(@"%f", outputTime->hostTime/1000.0/1000.0/1000.0);
	[(__bridge GLView *)displayLinkContext displayLinkCallback];
	return kCVReturnSuccess;
}
#endif

- (void)setTimescale:(float)scale{
	if(_firstRenderTick != 0){
		double renderTime = _timescale * (_secondRenderTick - _firstRenderTick);
		renderTime /= scale;
		_firstRenderTick = _secondRenderTick - renderTime;
	}
	_timescale = scale;
}

- (void)setMaxFPS:(float)fps{
	_limitRefreshInterval = 1.0/fps;
}

- (BOOL)isOpenGLReady{
	@synchronized(self){
		return _isOpenGLReady;
	}
}

- (void)setIsOpenGLReady:(BOOL)isReady{
	@synchronized(self){
		_isOpenGLReady = isReady;
	}
}

- (void)displayLinkCallback{
	if(!self.isOpenGLReady){
		return;
	}

	// 此变量是每个任务相关的，不同的任务得到的此变量的值可能不一样。queue的工作原理是拷贝上下文变量
	BOOL isBlocked = NO;
	@synchronized(self){
		if(_isRendering){
			isBlocked = YES;
		}
	}

	double currentTime = mach_absolute_time()/1000.0/1000.0/1000.0;

	// 只在主线程中渲染，因为处理用户交互是在主线程中，
	dispatch_async(dispatch_get_main_queue(), ^{
		// 定时器可能已经停止了，但任务还在积压，忽略这些任务
		if(!CVDisplayLinkIsRunning(_displayLink)){
			return;
		}
		
		// 只在主线程中修改这些变量
		if(_firstRenderTick == 0){
			_firstRenderTick = currentTime;
			_secondRenderTick = currentTime;
		}else{
			// 刷新频率限制
			if(currentTime - _secondRenderTick < _limitRefreshInterval){
				return;
			}
			
			if(_pauseRenderTick != 0){
				_firstRenderTick += (currentTime - _pauseRenderTick);
				_pauseRenderTick = 0;
			}
			_secondRenderTick = currentTime;
		}
		
		double frameTime = _timescale * (_secondRenderTick - _firstRenderTick);
		
		if(isBlocked){
			// log_debug(@"drop frame at %.3f", frameTime);
			return;
		}
		
		@synchronized(self){
			_isRendering = YES;
		}
		[self renderAtTime:frameTime];
		@synchronized(self){
			_isRendering = NO;
		}
	});
}

@end

