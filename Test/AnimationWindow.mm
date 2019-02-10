#import "AnimationWindow.h"
#import "MyOpenGLView.h"
#include "a3d/a3d.h"
using namespace a3d;

@interface AnimationWindow ()
@property (weak) IBOutlet NSView *contentView;
@property (weak) IBOutlet NSTextField *timeLabel;

@property GLContext *context;
@property GLDrawable *drawable;
@property Camera *camera;
@property SpriteNode *node;

@property double time;

@end

@implementation AnimationWindow

- (IBAction)onTimeScroll:(id)sender {
	NSSlider *slider = (NSSlider *)sender;
	_time = slider.floatValue * 10;
	[self draw];
}

- (void)windowDidLoad {
	[super windowDidLoad];
	[(NSView *)self.contentView setWantsLayer:YES];
	
	CGRect frame = self.window.frame;
	frame.size.width = 900;
	frame.size.height = 600;
	[self.window setFrame:frame display:YES animate:NO];
	
	int width = self.contentView.frame.size.width;
	int height = self.contentView.frame.size.height;

	log_debug("");
	_context = GLContext::create();
	log_debug("");

	_drawable = GLDrawable::create(width, height, 0);
	_camera = Camera::create();
	_camera->setup(60, width, height, width*10, -600);

	_node = new SpriteNode();
	Sprite *sprite = Sprite::imageSprite("/Users/ideawu/Downloads/imgs/1.jpg");
	_node->sprite(sprite);
	{
		a3d::Animate *action = a3d::Animate::rotate(180, Vector3(0, 1, 0));
		action->disposable(false);
		action->easingFunc(a3d::TimingFuncLinear);
		action->beginTime(0);
		action->duration(3);
		_node->runAnimation(action);
	}
	{
		a3d::Animate *action = a3d::Animate::rotate(180, Vector3(0, 1, 0));
		action->disposable(false);
		action->easingFunc(a3d::TimingFuncLinear);
		action->beginTime(-3);
		action->duration(3);
		_node->runAnimation(action);
	}

	_time = 0;

	[self draw];
}

- (void)draw{
	_timeLabel.stringValue = [NSString stringWithFormat:@"%.2f", _time];
	{
		_drawable->begin();
		_drawable->clear(0.1, 1, 0.1);

		_camera->view3D();
		_node->renderAtTime(_time);
		
		_drawable->finish();
	}

	CGImageRef _CGImage = _drawable->bitmap()->CGImage();

	NSImage *img = [[NSImage alloc] initWithCGImage:_CGImage size:NSMakeSize(_drawable->width(), _drawable->height())];
	self.contentView.layer.transform = CATransform3DConcat(CATransform3DMakeScale(1, -1, 1),
														   CATransform3DMakeTranslation(0, _drawable->height(), 0));
	self.contentView.layer.contents = img;
	[self.contentView setNeedsDisplay:YES];
}

- (void)keyDown:(NSEvent *)event{
	double df = 0.1;
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

@end
