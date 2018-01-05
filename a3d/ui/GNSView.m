//  Created by ideawu on 02/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GNSView.h"

@interface GNSView(){
	NSTrackingArea *_trackingArea;
}
@end

@implementation GNSView

- (id)init{
	self = [self initWithFrame:NSMakeRect(0, 0, 1, 1)];
	return self;
}

- (id)initWithFrame:(NSRect)frameRect {
	log_debug(@"%s", __func__);
	NSOpenGLPixelFormatAttribute attrs[] = {
		NSOpenGLPFANoRecovery, // Enable automatic use of OpenGL "share" contexts.
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFAAlphaSize, 8,
		NSOpenGLPFADepthSize, 16,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAAccelerated,
		0
	};
	NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
	self = [super initWithFrame:frameRect pixelFormat:pixelFormat];
	_mouseBasePoint.x = -1;
	return self;
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
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

- (NSPoint)mousePoint:(NSEvent *)event{
	NSPoint pos = [event locationInWindow];
	pos = [self convertPoint:pos fromView:nil];
	return pos;
}

- (void)mouseEntered:(NSEvent *)event{
	NSPoint pos = [self mousePoint:event];
	_mouseBasePoint.x = pos.x - _mouseTranslate.x;
	_mouseBasePoint.y = pos.y - _mouseTranslate.y;
//	log_debug(@"%s (%.2f, %.2f)", __func__, pos.x, pos.y);
}

- (void)mouseExited:(NSEvent *)event{
//	NSPoint pos = [self mousePoint:event];
//	log_debug(@"%s (%.2f, %.2f)", __func__, pos.x, pos.y);
}

- (void)mouseMoved:(NSEvent *)event{
	NSPoint pos = [self mousePoint:event];
//	log_debug(@"%s (%.2f, %.2f)", __func__, pos.x, pos.y);
	_mouseTranslate.x = pos.x - _mouseBasePoint.x;
	_mouseTranslate.y = pos.y - _mouseBasePoint.y;
}

@end
