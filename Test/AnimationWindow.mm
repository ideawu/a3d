#import "AnimationWindow.h"
#import "MyOpenGLView.h"
#include "a3d/a3d.h"
using namespace a3d;

@interface AnimationWindow ()
@property MyOpenGLView *videoView;
@property GLContext *context;
@end

@implementation AnimationWindow

- (void)windowDidLoad {
	[super windowDidLoad];
	[(NSView *)self.window.contentView setWantsLayer:YES];
	
	CGRect frame = self.window.frame;
	frame.size.width = 900;
	frame.size.height = 600;
	[self.window setFrame:frame display:YES animate:NO];

//	_videoView = [[MyOpenGLView alloc] initWithFrame:((NSView *)self.window.contentView).bounds];
//	[self.window.contentView addSubview:_videoView];
//	[self.window makeFirstResponder:_videoView];
//	return;
	
	log_debug("");
	_context = GLContext::create();
	log_debug("");

	[self draw];
}

- (void)keyDown:(NSEvent *)event{
//	NSLog(@"%@", event);
	[self draw];
}

- (void)draw{
	int width = self.window.contentView.frame.size.width;
	int height = self.window.contentView.frame.size.height;
	
	SpriteNode *node = new SpriteNode();
	Sprite *sprite = Sprite::imageSprite("/Users/ideawu/Downloads/imgs/1.jpg");
	node->sprite(sprite);
//	node->move(10, 10, 10);
	
	GLDrawable *drawable = GLDrawable::create(width, height, 0);
	
	Camera *camera = Camera::create();
	camera->setup(60, width, height, width*10, -200);

	{
		drawable->begin();
		drawable->clear(0.1, 1, 0.1);

		camera->view3D();
		node->renderAtTime(0);
		
		drawable->finish();
	}

	log_debug("");
	CGImageRef _CGImage = drawable->bitmap()->CGImage();
	log_debug("");

	{
		NSImage *img = [[NSImage alloc] initWithCGImage:_CGImage size:NSMakeSize(width, height)];
		self.window.contentView.layer.contents = img;
		[self.window.contentView setNeedsDisplay:YES];
	}
}

@end
