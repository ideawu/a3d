//  Created by ideawu on 2/18/19.
//  Copyright © 2019 ideawu. All rights reserved.
//

#import "TestTransparency.h"
#include "a3d/a3d.h"
using namespace a3d;

@interface TestTransparency ()
@property (weak) IBOutlet NSView *contentView;

@property Context *context;
@property Drawable *drawable;
@property Camera *camera;
@property SpriteNode *node1;
@property SpriteNode *node2;
@property SpriteNode *node22;

@end

@implementation TestTransparency

- (void)windowDidLoad {
    [super windowDidLoad];
	[(NSView *)self.contentView setWantsLayer:YES];

	CGRect frame = self.window.frame;
	frame.size.width = 900;
	frame.size.height = 600;
	[self.window setFrame:frame display:YES animate:NO];
	
	int width = self.contentView.bounds.size.width;
	int height = self.contentView.bounds.size.height;
	
	_context = Context::create();
	//_drawable = Drawable::create(width*2, height*2, 0); // retina @2x
	_drawable = Drawable::create(width*1, height*1, 0);
	_camera = Camera::create();
	_camera->setup(60, width, height, width*10, -600);
	
	{
		_node1 = new SpriteNode();
		Sprite *sprite = Sprite::imageSprite("/Users/ideawu/Downloads/imgs/1.jpg");
		_node1->sprite(sprite);
		_node1->opacity(1);
	}
	
	{
		_node2 = new SpriteNode();
		Sprite *sprite = Sprite::imageSprite("/Users/ideawu/Downloads/imgs/9.jpg");
		_node2->sprite(sprite);
		_node2->opacity(0.6);
		{
			_node22 = new SpriteNode();
			Sprite *sprite = Sprite::imageSprite("/Users/ideawu/Downloads/imgs/2.jpg");
			_node22->sprite(sprite);
			_node22->x(300);
			_node22->opacity(0.5);
			_node2->addSubnode(_node22);
		}
	}

	[self draw];
}

- (void)draw{
//	glDepthMask(GL_FALSE);
//	glDepthMask(GL_TRUE);

	{
		_context->makeCurrent();
		
		_drawable->begin();
		_drawable->clear(1, 1, 1);
		
		_camera->view3D();
		_node1->renderAtTime(0);
		_node2->renderAtTime(0);

		_drawable->finish();
	}
	
	CGImageRef _CGImage = _drawable->bitmap()->CGImage();
	
	NSImage *img = [[NSImage alloc] initWithCGImage:_CGImage size:NSMakeSize(_drawable->width(), _drawable->height())];
	_contentView.layer.transform = CATransform3DConcat(CATransform3DMakeScale(1, -1, 1), CATransform3DMakeTranslation(0, _contentView.bounds.size.height, 0));
	_contentView.layer.contents = img;
	[_contentView setNeedsDisplay:YES];
}

- (void)keyDown:(NSEvent *)event{
	[self draw];
}

@end
