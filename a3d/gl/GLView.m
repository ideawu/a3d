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
// renderTime = second - first
@property double firstRenderTick;
// 如果渲染成功，second 要滑动
@property double secondRenderTick;
// fail 记录上一次second滑动失败的时钟，如果 pause 恢复，将 first和second 整体滑动到 pause 处，然后 second 继续滑动
@property double failureRenderTick;
@property double lastAbsoluteTime;
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
	[self invokeRender:time];
}
#else
static CVReturn displayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *now,
									const CVTimeStamp *outputTime, CVOptionFlags flagsIn,
									CVOptionFlags *flagsOut, void *displayLinkContext){
	[(__bridge GLView *)displayLinkContext callRender];
	return kCVReturnSuccess;
}
#endif

- (void)callRender{
	double currentTime = mach_absolute_time()/1000.0/1000.0/1000.0;
	// 只在主线程中渲染，因为处理用户交互是在主线程中，
	// 同步等待渲染完成，不然 main queue 可能积累太多渲染任务。
	dispatch_sync(dispatch_get_main_queue(), ^{
		if(self.isOpenGLReady){
			if(_firstRenderTick == 0){
				_firstRenderTick = currentTime;
				_secondRenderTick = currentTime;
			}
			
			double renderTime = _secondRenderTick - _firstRenderTick;
			BOOL ret = [self renderAtTime:renderTime];
			if(!ret){
				_failureRenderTick = currentTime;
			}else{
				// 如果是从失败中恢复
				if(_failureRenderTick != 0){
					_firstRenderTick = _failureRenderTick - renderTime;
					// 清除失败标记
					_failureRenderTick = 0;
				}
				_secondRenderTick = currentTime;
			}
		}
	});
}

@end

