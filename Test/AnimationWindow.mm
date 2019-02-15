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
	
	int width = self.contentView.bounds.size.width;
	int height = self.contentView.bounds.size.height;

	log_debug("");
	_context = GLContext::create();
	log_debug("");

	//_drawable = GLDrawable::create(width*2, height*2, 0); // retina @2x
	_drawable = GLDrawable::create(width*1, height*1, 0);
	_camera = Camera::create();
	_camera->setup(60, width, height, width*10, -600);

	_node = new SpriteNode();
//	_node->isLooping(false);
//	Sprite *sprite = Sprite::imageSprite("/Users/ideawu/Downloads/imgs/9.jpg");
	Sprite *sprite = Sprite::imageSprite("/Users/ideawu/Downloads/gif/ha.gif");
//	Sprite *sprite = Sprite::textSprite("Hello World! 你好！", 50, Color::yellow());
	_node->sprite(sprite);
	{
		a3d::Animate *action = a3d::Animate::rotate(360, Vector3(0, 1, 0));
		action->disposable(false);
		action->easingFunc(a3d::TimingFuncLinear);
		action->beginTime(-2.5);
		action->duration(5);
		_node->runAnimation(action);
	}

	_time = 0;

	[self draw];
	
//	NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval:0.5 repeats:YES block:^(NSTimer *timer) {
//		log_debug("");
//	}];
//	// 为避免 NSButton 等按住的时候卡住 timer，需要将 timer 的 runmode 设为 NSRunLoopCommonModes
//	[[NSRunLoop mainRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
}

- (void)draw{
	_timeLabel.stringValue = [NSString stringWithFormat:@"%.3f", _time];
	{
		_context->makeCurrent();

		_drawable->begin();
		_drawable->clear(0.1, 0.1, 0.1);

		_camera->view3D();
		_node->renderAtTime(_time);
		
		_drawable->finish();
	}
	
	CGImageRef _CGImage = _drawable->bitmap()->CGImage();

	NSImage *img = [[NSImage alloc] initWithCGImage:_CGImage size:NSMakeSize(_drawable->width(), _drawable->height())];
	_contentView.layer.transform = CATransform3DConcat(CATransform3DMakeScale(1, -1, 1), CATransform3DMakeTranslation(0, _contentView.bounds.size.height, 0));
	_contentView.layer.contents = img;
	[_contentView setNeedsDisplay:YES];
}

- (void)keyDown:(NSEvent *)event{
	unichar c = [[event charactersIgnoringModifiers] characterAtIndex:0];
	switch(c){
		case 'q':
		case 'Q':{
			[self.window close];
			break;
		}
	}
	
//	[self draw];
}

@end
