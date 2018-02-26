//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "A3DView.h"
#import "A3DLayer.h"
#include "Clock.h"

using namespace a3d;

typedef struct{
	float fps;
	double beginTime;
	double lastTime;
	int count;
}RefreshRate;

@interface A3DView(){
	NSTrackingArea *_trackingArea;
#if TARGET_OS_IPHONE
	CADisplayLink *_displayLink;
#else
	CVDisplayLinkRef _displayLink;
#endif
//	dispatch_queue_t _processQueue;

	Clock _clock;

	float _maxFPS;
}
@property BOOL isRendering;
@property RefreshRate refreshRate;
@property NSTimer *statisicsTimer;
@property NSTextField *statisticsLabel;
@end

@implementation A3DView

+ (NSOpenGLPixelFormat*)defaultPixelFormat{
	NSOpenGLPixelFormatAttribute attrs[] = {
		NSOpenGLPFANoRecovery,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFADepthSize, 16,
		NSOpenGLPFAAlphaSize, 8,
//		NSOpenGLPFAStencilSize, 8,
//		NSOpenGLPFAMultisample,
//		NSOpenGLPFASampleBuffers, 1,
//		NSOpenGLPFASamples, 4,
		0
	};
	NSOpenGLPixelFormat* pixelFormat = nil;
	pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
	return pixelFormat;
}

+ (NSOpenGLContext*)defaultOpenGLContext{
	static NSOpenGLContext *context = nil;
	@synchronized(context){
		if(context == nil){
			NSOpenGLPixelFormat* pixelFormat = [A3DView defaultPixelFormat];
			context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
		}
	}
	return context;
}

- (id)initWithFrame:(NSRect)frameRect{
	self = [super initWithFrame:frameRect];
	_pixelFormat = [A3DView defaultPixelFormat];
	_openGLContext = [[NSOpenGLContext alloc] initWithFormat:_pixelFormat
												shareContext:[A3DView defaultOpenGLContext]];
	[self.openGLContext makeCurrentContext];

	_displayLink = NULL;
	_refreshRate.fps = 0;
	_refreshRate.beginTime = 0;
	_refreshRate.count = 0;
	_maxFPS = 100;

	[self setupOpenGL];

	return self;
}

- (void)dealloc{
//	log_debug(@"%s", __func__);
}

- (void)viewDidMoveToSuperview{
	if(self.superview){
		[self onReshape];
		
		[[NSNotificationCenter defaultCenter] addObserver:self
												 selector:@selector(onReshape)
													 name:NSViewFrameDidChangeNotification
												   object:self];
		// 在 superview.wantsLayer 的情况下，NSViewGlobalFrameDidChangeNotification 不可用！FUCK Apple!
	}else{
		CGLLockContext([self.openGLContext CGLContextObj]);
		[self.openGLContext makeCurrentContext];
		[self clean];
		[self.openGLContext update];
		CGLUnlockContext([self.openGLContext CGLContextObj]);
		
		if(_statisicsTimer){
			[_statisicsTimer invalidate];
		}
		if(_displayLink){
			[self freeDisplayLink];
		}
		[[NSNotificationCenter defaultCenter] removeObserver:self
														name:NSViewFrameDidChangeNotification
													  object:self];
	}
}

- (void)setupOpenGL{
//	log_debug(@"%s", __func__);
	// Synchronize buffer swaps with vertical refresh rate
//	GLint swapInt = 1;
//	[self.openGLContext setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
	
	[self setWantsLayer:YES];
	[self setWantsBestResolutionOpenGLSurface:YES];

	[self setup];
	[self startAnimation];
}

- (void)onReshape{
//	log_debug(@"%s", __func__);
	// 操作前务必要切换上下文
	CGLLockContext([self.openGLContext CGLContextObj]);
	[self.openGLContext makeCurrentContext];
	[self reshape];
	[self.openGLContext update];
	CGLUnlockContext([self.openGLContext CGLContextObj]);
}

- (void)viewWillStartLiveResize{
	// avoid choppy while live resizing
	[(A3DLayer*)self.layer setAsynchronous:NO];
}

- (void)viewDidEndLiveResize{
	[(A3DLayer*)self.layer setAsynchronous:YES];
}

- (CALayer *)makeBackingLayer{
//	log_debug(@"%s", __func__);
	A3DLayer *layer = [[A3DLayer alloc] init];
	layer.openGLPixelFormat = self.pixelFormat;
	layer.openGLContext = self.openGLContext;
	[layer setAsynchronous:YES];
//	[layer setNeedsDisplayOnBoundsChange:YES];
	return layer;
}

- (CGSize)viewportSize{
	return self.bounds.size;
}

- (CGSize)framebufferSize{
	return [self convertSizeToBacking:self.bounds.size];
}

- (void)setup{
}

- (void)clean{
}

- (void)resize{
}

- (void)reshape{
	[self resize];
}

- (float)fps{
	return _refreshRate.fps;
}

- (void)setMaxFPS:(float)fps{
	if(fps <= 0){
		return;
	}
	_maxFPS = fps;
}

- (void)setTimescale:(double)scale{
	_clock.speed(scale);
}

#pragma mark - Statistics label

- (void)showStatistics{
	if(!_statisicsTimer){
		_statisicsTimer = [NSTimer scheduledTimerWithTimeInterval:0.3
														   target:self
														 selector:@selector(updateStatisticsLabel)
														 userInfo:nil
														  repeats:YES];
		_statisticsLabel = [[NSTextField alloc] initWithFrame:CGRectMake(0, 0, 80, 18)];
		_statisticsLabel.bordered = NO;
		_statisticsLabel.selectable = NO;
		_statisticsLabel.editable = NO;
		_statisticsLabel.bezeled = NO;
		_statisticsLabel.textColor = [NSColor whiteColor];
		_statisticsLabel.drawsBackground = YES;
		_statisticsLabel.backgroundColor = [NSColor grayColor];
		[self addSubview:_statisticsLabel];
	}
}

- (void)hideStatistics{
	if(_statisicsTimer){
		[_statisicsTimer invalidate];
		_statisicsTimer = nil;
		
		[_statisticsLabel removeFromSuperview];
		_statisticsLabel = nil;
	}
}

- (void)updateStatisticsLabel{
	if(_statisticsLabel){
		_statisticsLabel.stringValue = [NSString stringWithFormat:@"fps: %.2f", _refreshRate.fps];
	}
}

#pragma mark - Keyboard and Mouse event handle

- (BOOL)acceptsFirstResponder{
	return YES;
}

- (void)updateTrackingAreas{
	if(_trackingArea){
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
		_clock.update(a3d::absolute_time());
		_clock.start();
	}
}

- (void)stopAnimation{
	if(_displayLink && CVDisplayLinkIsRunning(_displayLink)){
		[self stopDisplayLink];
		_clock.update(a3d::absolute_time());
		_clock.pause();
	}
}

- (void)toggleAnimation{
	if(self.isAnimating){
		[self stopAnimation];
	}else{
		[self startAnimation];
	}
}

- (BOOL)isAnimating{
	return _displayLink && CVDisplayLinkIsRunning(_displayLink);
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
	[(__bridge A3DView *)displayLinkContext displayLinkCallback];
	return kCVReturnSuccess;
}
#endif

- (void)displayLinkCallback{
	// 此变量是每个任务相关的，不同的任务得到的此变量的值可能不一样。queue的工作原理是拷贝上下文变量
	// 要在主线程中更新时钟，所以这里不直接丢弃任务，而是在主线程中再丢弃任务
	BOOL isBlocked = NO;
	@synchronized(self){
		if(_isRendering){
			isBlocked = YES;
		}
	}

	// 只在主线程中渲染，因为处理用户交互是在主线程中，
	dispatch_async(dispatch_get_main_queue(), ^{
		// 定时器可能已经停止了，但任务还在积压，忽略这些任务
		if(!CVDisplayLinkIsRunning(_displayLink)){
			return;
		}
		if(isBlocked){
			log_debug(@"drop frame at %.3f", _clock.time());
			return;
		}
		[self updateClock];
		if(_refreshRate.fps > _maxFPS){
//			log_debug(@"limit fps: %.1f, max: %.1f", _refreshRate.fps, _maxFPS);
			return;
		}

		@synchronized(self){
			_isRendering = YES;
		}
		if(self.layer){
			[(A3DLayer*)self.layer setCanDraw:YES];
			if(self.inLiveResize){
				// live resizing 过程，如果 frameSize 未发生变动，则 view 不会重绘，
				// 所以这里强制要求 view 重绘。否则，等 layer 被 AppKit 询问是否重绘(canDraw)。
				[self setNeedsDisplay:YES];
			}
		}else{
			[self doRender];
		}
		@synchronized(self){
			_isRendering = NO;
		}
	});
}

// 必须在主线程中
- (void)doRender{
//	double idealInterval = 0.016713;
//	CVTime ct = CVDisplayLinkGetNominalOutputVideoRefreshPeriod(_displayLink);
//	if(ct.timeScale > 0){
//		idealInterval = (double)ct.timeValue/ct.timeScale;
//	}
	double maxInterval = fmax(1.0/_maxFPS, 0.050);
	double interval = _clock.time() - _refreshRate.lastTime;
	if(interval > maxInterval){
		interval = maxInterval;
	}
	
//	static double last_time = a3d::absolute_time();
//	if(interval == maxInterval){
//		log_debug(@"render interval: %.3f, %.3f", interval, a3d::absolute_time() - last_time);
//	}
//	last_time = a3d::absolute_time();

	_refreshRate.count ++;
//	_refreshRate.lastTime = _clock.time();
	_refreshRate.lastTime += interval;

//	log_debug(@"begin %.3f", _refreshRate.lastTime);
	CGLLockContext([self.openGLContext CGLContextObj]);
	[self.openGLContext makeCurrentContext];
	[self renderAtTime:_refreshRate.lastTime];
	[self.openGLContext flushBuffer];
	CGLUnlockContext([self.openGLContext CGLContextObj]);
//	log_debug(@"end");
}

- (void)drawRect:(NSRect)dirtyRect{
	[self doRender];
}

//- (BOOL)preservesContentDuringLiveResize{
//	return YES;
//}

- (void)setFrameSize:(NSSize)newSize{
	[super setFrameSize:newSize];
	if(self.inLiveResize){
		// 在 10.9 等低版本，live resizing 过程 main queue 会阻塞，
		// 导致时钟无法更新，所以要在这里更新
		[self updateClock];
		if(_refreshRate.fps > _maxFPS){
			return;
		}
	}
	[self setNeedsDisplay:YES];
	[(A3DLayer*)self.layer setCanDraw:YES];
}

- (void)lockFocus{
	[super lockFocus];
	if(self.openGLContext.view != self){
		self.openGLContext.view = self;
	}
}

- (void)updateClock{
	double tick = a3d::absolute_time();
	_clock.update(tick);
	
	// 初始化
	if(_refreshRate.beginTime == 0){
		_refreshRate.fps = 0;
		_refreshRate.beginTime = _clock.time();
		_refreshRate.lastTime = _refreshRate.beginTime;
		_refreshRate.count = 0;
	}
	// 更新 fps 统计
	double interval = _clock.time() - _refreshRate.beginTime;
	_refreshRate.fps = interval==0? 0 : (_refreshRate.count/interval);
	if(interval > 1){ // 每秒重新统计
		_refreshRate.beginTime = _clock.time();
		_refreshRate.count = 0;
	}
}

- (void)renderAtTime:(double)time{
}

@end

