//  Created by ideawu on 26/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "TestController.h"
#import "MyOpenGLView.h"

@interface TestController ()<NSWindowDelegate>{
	double offset;
}
@property NSWindow *window;
@property MyOpenGLView *videoView;
@end

@implementation TestController

- (void)windowDidLoad {
	[super windowDidLoad];


	CGRect frame = self.window.frame;
	frame.size.width = 900;
	frame.size.height = 600;
	[self.window setFrame:frame display:YES animate:NO];

	_videoView = [[MyOpenGLView alloc] initWithFrame:((NSView *)self.window.contentView).frame];
	[self.window.contentView addSubview:_videoView];
	[self.window makeFirstResponder:_videoView];
}

- (void)keyDown:(NSEvent *)event{
	[_videoView keyDown:event];
}

- (void)windowDidResize:(NSNotification *)notification{
	_videoView.frame = ((NSView *)self.window.contentView).frame;
}

@end
