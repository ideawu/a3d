//  Created by ideawu on 26/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "TestController.h"
#import "MyOpenGLView.h"

@interface TestController (){
	double offset;
}
@property MyOpenGLView *videoView;
@end

@implementation TestController

- (void)windowDidLoad {
    [super windowDidLoad];

	
	CGRect frame = self.window.frame;
	frame.size.width = 900;
	frame.size.height = 600;
	[self.window setFrame:frame display:YES animate:NO];
	
	CGFloat width = frame.size.width - 100;
	CGFloat height = frame.size.height - 100;
	CGFloat x = (frame.size.width - width)/2;
	CGFloat y = (frame.size.height - height)/2;
	
	CGRect frame2 = CGRectMake(x, y, width, height);
	_videoView = [[MyOpenGLView alloc] initWithFrame:frame2];
	[self.window.contentView addSubview:_videoView];
	[self.window makeFirstResponder:_videoView];
}

- (void)keyDown:(NSEvent *)event{
	[_videoView keyDown:event];
}

@end
