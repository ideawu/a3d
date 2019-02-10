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

- (void)dealloc{
	log_debug(@"%s", __func__);
}

- (void)windowDidLoad {
	[super windowDidLoad];
	[(NSView *)self.window.contentView setWantsLayer:YES];

	CGRect frame = self.window.frame;
	frame.size.width = 900;
	frame.size.height = 600;
	[self.window setFrame:frame display:YES animate:NO];

	_videoView = [[MyOpenGLView alloc] initWithFrame:((NSView *)self.window.contentView).bounds];
	[self.window.contentView addSubview:_videoView];
	[self.window makeFirstResponder:_videoView];

	{
		NSImageView *view = [[NSImageView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
		view.image = [NSImage imageNamed:@"alex.png"];
		[self.window.contentView addSubview:view];
	}
}

- (void)keyDown:(NSEvent *)event{
	[_videoView keyDown:event];
}

- (void)windowDidResize:(NSNotification *)notification{
	_videoView.frame = ((NSView *)self.window.contentView).frame;
}

- (void)windowWillClose:(NSNotification *)notification{
//	log_debug(@"%s", __func__);
	[_appDelegate windowWillClose:self];
	[_videoView removeFromSuperview];
	_videoView = nil;
}

@end
