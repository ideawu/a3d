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
	return self;
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

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

@end
