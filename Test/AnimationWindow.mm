#import "AnimationWindow.h"

@interface AnimationWindow ()

@end

@implementation AnimationWindow

- (void)windowDidLoad {
	[super windowDidLoad];
	[(NSView *)self.window.contentView setWantsLayer:YES];
	
	CGRect frame = self.window.frame;
	frame.size.width = 900;
	frame.size.height = 600;
	[self.window setFrame:frame display:YES animate:NO];
	
//	_videoView = [[MyOpenGLView alloc] initWithFrame:((NSView *)self.window.contentView).frame];
//	[self.window.contentView addSubview:_videoView];
//	[self.window makeFirstResponder:_videoView];
}

@end
