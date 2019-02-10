#import "AnimationWindow.h"
#import "MyOpenGLView.h"
#include "a3d/a3d.h"
using namespace a3d;

@interface AnimationWindow ()
@property MyOpenGLView *videoView;

@property GLContext *context;
@property GLDrawable *drawable;
@property Camera *camera;
@property SpriteNode *node;

@property double time;

@end

@implementation AnimationWindow

- (void)windowDidLoad {
	[super windowDidLoad];
	[(NSView *)self.window.contentView setWantsLayer:YES];
	
	CGRect frame = self.window.frame;
	frame.size.width = 900;
	frame.size.height = 600;
	[self.window setFrame:frame display:YES animate:NO];
	
	int width = self.window.contentView.frame.size.width;
	int height = self.window.contentView.frame.size.height;

	log_debug("");
	_context = GLContext::create();
	log_debug("");

	_drawable = GLDrawable::create(width, height, 0);
	_camera = Camera::create();
	_camera->setup(60, width, height, width*10, -200);

	_node = new SpriteNode();
	Sprite *sprite = Sprite::imageSprite("/Users/ideawu/Downloads/imgs/1.jpg");
	_node->sprite(sprite);
	{
//		a3d::Animate *action = a3d::Animate::rotate(60, Vector3(0, 0, 1));
		a3d::Animate *action = a3d::Animate::move(100, 0, 0);
		action->easingFunc(a3d::TimingFuncLinear);
		action->duration(1);
		_node->runAnimation(action);
	}
	
	_time = 0;

	[self draw];
}

- (void)keyDown:(NSEvent *)event{
	double df = 0.05;
	unichar c = [[event charactersIgnoringModifiers] characterAtIndex:0];
	switch(c){
		case 'q':
		case 'Q':{
			[self.window close];
			break;
		}
		case NSLeftArrowFunctionKey:{
			_time -= df;
			break;
		}
		case NSRightArrowFunctionKey:{
			_time += df;
			break;
		}
	}
	
	[self draw];
}

- (void)draw{
	{
		_drawable->begin();
		_drawable->clear(0.1, 1, 0.1);

		_camera->view3D();
		_node->renderAtTime(_time);
		log_debug("%.2f %.2f", _time, _node->position().x);
		
		_drawable->finish();
	}

	log_debug("");
	CGImageRef _CGImage = _drawable->bitmap()->CGImage();
	log_debug("");

	{
		if(self.window.contentView.layer.contents){
			self.window.contentView.layer.contents = nil;
		}else{
		}
		NSImage *img = [[NSImage alloc] initWithCGImage:_CGImage size:NSMakeSize(_drawable->width(), _drawable->height())];
		self.window.contentView.layer.contents = img;
		[self.window.contentView setNeedsDisplay:YES];
	}
}

@end
