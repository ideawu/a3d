//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "A3DView2.h"
#include "Clock.h"

using namespace a3d;

typedef struct{
	float fps;
	double beginTime;
	double lastTime;
	int count;
}RefreshRate;

@interface A3DView2(){
	NSTrackingArea *_trackingArea;
#if TARGET_OS_IPHONE
	CADisplayLink *_displayLink;
#else
	CVDisplayLinkRef _displayLink;
#endif
	//	dispatch_queue_t _processQueue;

	Clock _clock;

	float _maxFPS;
	BOOL _isOpenGLReady;
}
@property BOOL isRendering;
@property RefreshRate refreshRate;
@property NSTimer *statisicsTimer;
@property NSTextField *statisticsLabel;
@end

@implementation A3DView2

+ (NSOpenGLPixelFormat*)defaultPixelFormat{
	NSOpenGLPixelFormatAttribute attrs[] = {
		NSOpenGLPFANoRecovery,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFADepthSize, 16,
		NSOpenGLPFAAlphaSize, 8,
		NSOpenGLPFAStencilSize, 8,
		NSOpenGLPFAMultisample,
		NSOpenGLPFASampleBuffers, 1,
		NSOpenGLPFASamples, 4,
		0
	};
	NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
	return pixelFormat;
}

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format{
	if(!format){
		format = A3DView2.defaultPixelFormat;
	}
	self = [super initWithFrame:frameRect pixelFormat:format];

	{
		GLuint tid;
		glGenTextures(1, &tid);
		log_debug(@"%d", tid);
	}
	log_debug(@"%@ %@", self.openGLContext, [NSOpenGLContext currentContext]);

	[self setWantsLayer:YES];
	NSOpenGLLayer *layer = (NSOpenGLLayer *)self.layer;
	log_debug(@"%@", layer);
	log_debug(@"%@ %@", self.openGLContext, [NSOpenGLContext currentContext]);
	{
		GLuint tid;
		glGenTextures(1, &tid);
		log_debug(@"%d", tid);
	}
	[self setWantsBestResolutionOpenGLSurface:YES];

	_displayLink = NULL;
	_isOpenGLReady = NO;

	_refreshRate.fps = 0;
	_refreshRate.beginTime = 0;
	_refreshRate.count = 0;
	_maxFPS = 100;

	return self;
}

- (void)dealloc{
	if(_displayLink){
		[self freeDisplayLink];
	}
}

- (void)setup{
}

- (void)prepareOpenGL{
	log_debug(@"%s", __func__);
	log_debug(@"%@", self.layer);
	[super prepareOpenGL];
	{
		GLuint tid;
		glGenTextures(1, &tid);
		log_debug(@"%d", tid);
	}
	log_debug(@"%@ %@", self.openGLContext, [NSOpenGLContext currentContext]);
	// 操作前务必要切换上下文
	CGLLockContext([[self openGLContext] CGLContextObj]);
	[self.openGLContext makeCurrentContext];
	{
		GLuint tid;
		glGenTextures(1, &tid);
		log_debug(@"%d", tid);
	}
	log_debug(@"%@ %@", self.openGLContext, [NSOpenGLContext currentContext]);

	[self setup];
	[self startAnimation];
	// 如果 OpenGL 没有 ready 就执行动画线程，会出错
	[self setIsOpenGLReady:YES];
	CGLUnlockContext([[self openGLContext] CGLContextObj]);
}

- (void)resize{
}

- (void)reshape{
	// 操作前务必要切换上下文
	CGLLockContext([[self openGLContext] CGLContextObj]);
	[[self openGLContext] makeCurrentContext];
	[self resize];
	CGLUnlockContext([[self openGLContext] CGLContextObj]);
}

- (CGSize)viewportSize{
	return self.bounds.size;
}

- (CGSize)framebufferSize{
	return [self convertSizeToBacking:self.bounds.size];
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
	[(__bridge A3DView2 *)displayLinkContext displayLinkCallback];
	return kCVReturnSuccess;
}
#endif

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
	_statisticsLabel.stringValue = [NSString stringWithFormat:@"fps: %.2f", _refreshRate.fps];
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

		double tick = a3d::absolute_time();
		_clock.update(tick);

		if(isBlocked){
			log_debug(@"drop frame at %.3f", _clock.time());
			return;
		}

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

		if(_refreshRate.fps > _maxFPS){
			//			log_debug(@"limit fps: %.1f, max: %.1f", _refreshRate.fps, _maxFPS);
			return;
		}
		//		log_debug(@"%.3f, %.3f %d", _refreshRate.fps, _refreshRate.beginTime, _refreshRate.count);

		double realInterval = _clock.time() - _refreshRate.lastTime;

		// 在慢机器上时间平滑反而影响效果
		//		// 设备理想刷新周期
		//		double idealInterval = 0.016713;
		//		CVTime ct = CVDisplayLinkGetNominalOutputVideoRefreshPeriod(_displayLink);
		//		if(ct.timeScale > 0){
		//			idealInterval = (double)ct.timeValue/ct.timeScale;
		//		}
		//		double bestInterval = fmax(1.0/_maxFPS, idealInterval);
		//		if(realInterval < 0){
		//			return;
		//		}else if(realInterval > bestInterval * 4){
		//			log_debug(@"realInterval: %.3f bestInterval: %.3f", realInterval, bestInterval);
		//			// 已无平滑的必要，跳到指定时间
		//		}else if(realInterval > bestInterval * 1){
		//			log_debug(@"realInterval: %.3f bestInterval: %.3f", realInterval, bestInterval);
		//			realInterval =  0.6 * (realInterval - bestInterval) + bestInterval;
		//		}else if(realInterval < bestInterval){
		//			log_debug(@"realInterval: %.6f bestInterval: %.6f", realInterval, bestInterval);
		//			realInterval = bestInterval;
		//		}

		_refreshRate.lastTime += realInterval;

		@synchronized(self){
			_isRendering = YES;
		}
		// 在10.13之前，layer-backed只能在drawRect中渲染
		if(NSFoundationVersionNumber <= 1056.13 && self.layer != nil){
			[self setNeedsDisplay:YES];
		}else{
			[self doRender];
		}
		@synchronized(self){
			_isRendering = NO;
		}
	});
}

- (void)doRender{
	_refreshRate.count ++;
	CGLLockContext([[self openGLContext] CGLContextObj]);
	[[self openGLContext] makeCurrentContext];
	//	log_debug(@"begin");
	[self renderAtTime:_refreshRate.lastTime];
	//	log_debug(@"end");
	[[self openGLContext] flushBuffer];
	CGLUnlockContext([[self openGLContext] CGLContextObj]);
}

- (void)drawRect:(NSRect)dirtyRect{
	[super drawRect:dirtyRect];
	[self doRender];
}

- (void)renderAtTime:(double)time{
}


@end

