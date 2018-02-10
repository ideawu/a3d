//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "A3DView.h"
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
	BOOL _isOpenGLReady;
}
@property BOOL isRendering;
@property RefreshRate refreshRate;
@end

@implementation A3DView

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
//	_processQueue = NULL;
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
		_clock.resume();
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
	[(__bridge A3DView *)displayLinkContext displayLinkCallback];
	return kCVReturnSuccess;
}
#endif

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
//			log_debug(@"drop frame at %.3f", _clock.time());
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
		_refreshRate.fps = fmax(_maxFPS, _refreshRate.fps);
		if(interval > 1){ // 每秒重新统计
			_refreshRate.beginTime = _clock.time();
			_refreshRate.count = 0;
		}

		// 设备理想刷新周期
		double idealInterval = 0.016;
		CVTime ct = CVDisplayLinkGetNominalOutputVideoRefreshPeriod(_displayLink);
		if(ct.timeScale > 0){
			idealInterval = (double)ct.timeValue/ct.timeScale;
		}

		double bestInterval = fmax(1.0/_maxFPS, idealInterval);
		double realInterval = _clock.time() - _refreshRate.lastTime;
		if(realInterval < 0){
//			log_debug(@"limit fps: %.1f, max: %.1f", _refreshRate.fps, _maxFPS);
			return;
			// 在慢机器上时间平滑反而影响效果
//		}else if(realInterval > bestInterval * 4){
//			log_debug(@"realInterval: %.3f bestInterval: %.3f", realInterval, bestInterval);
//			// 已无平滑的必要，跳到指定时间
//		}else if(realInterval > bestInterval * 1){
//			log_debug(@"realInterval: %.3f bestInterval: %.3f", realInterval, bestInterval);
//			realInterval =  0.6 * (realInterval - bestInterval) + bestInterval;
		}else{
			realInterval = bestInterval;
		}

		_refreshRate.count ++;
		_refreshRate.lastTime += realInterval;

		@synchronized(self){
			_isRendering = YES;
		}
		[self renderAtTime:_refreshRate.lastTime];
		@synchronized(self){
			_isRendering = NO;
		}
	});
}

@end

