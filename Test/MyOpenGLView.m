#import "MyOpenGLView.h"
#import <GLKit/GLKit.h>

@interface MyOpenGLView(){
	GWorld *_world;
	GImage *_img1;
	GImage *_img2;
	GImage *_camera;
	float _rotateX;
	float _rotateY;
	int _auto_rotate_x;
	int _auto_rotate_y;
	GDraftScene *_scene;
}
@end

@implementation MyOpenGLView

- (void)prepareOpenGL {
	log_debug(@"%s", __func__);
	// 操作前务必要切换上下文
	[self.openGLContext makeCurrentContext];
	
	_rotateX = 0;
	_rotateY = 0;

	_world = [[GWorld alloc] init];
	_world.width = 10000;
	_world.height = 10000;
	_world.depth = 10000;
	_scene = [[GDraftScene alloc] init];
	_scene.width = _world.width;
	_scene.height = _world.height;
	_scene.depth = _world.depth;

	{
		NSString *filename = @"/Users/ideawu/Downloads/imgs/camera.jpg";
		_camera = [[GImage alloc] initWithContentsOfFile:filename];
		[_camera scale:0.1];
	}

	{
		NSString *filename = @"/Users/ideawu/Downloads/imgs/1.jpg";
		_img1 = [[GImage alloc] initWithContentsOfFile:filename];
		[_img1 scale:0.5];
		[_img1 moveX:_img1.width/2];
		[_img1 moveY:_img1.height/2];
		
		[_img1 moveX:300];
		[_img1 moveZ:300];
	}
	{
		NSString *filename = @"/Users/ideawu/Downloads/imgs/9.jpg";
		_img2 = [[GImage alloc] initWithContentsOfFile:filename];
		[_img2 moveX:_img2.width/2];
		[_img2 moveY:_img2.height/2];

		[_img2 moveX:2000];
		[_img2 moveZ:4000];
	}

//	[_img moveX:50];
//	[_img moveY:50];
}

- (void)reshape {
	log_debug(@"%s", __func__);
	// 操作前务必要切换上下文
	[[self openGLContext] makeCurrentContext];
	log_debug(@"%.2f %.2f", self.bounds.size.width, self.bounds.size.height);
	[_world setCameraWidth:self.bounds.size.width height:self.bounds.size.height depth:self.bounds.size.width*10];
}

- (void)drawRect:(NSRect)aRect {
	// 操作前务必要切换上下文
	[[self openGLContext] makeCurrentContext];

	[_world beginRender];
	[_world render3D];
	[self draw3D];
	[_world render2D];
	[self draw2D];
	[_world finishRender];
	
	[[self openGLContext] flushBuffer];
}

- (void)draw3D{
	[_img1 render];
	[_img2 render];
	[_scene render];
}

- (void)draw2D{
	float width = self.bounds.size.width;
	float height = self.bounds.size.height;

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x0f0f);
	glLineWidth(1);
	
	glColor4f(1, 0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	{
		glVertex3f(0, height/2, 0);
		glVertex3f(width, height/2, 0);
		glVertex3f(width/2, 50, 0);
		glVertex3f(width/2, height, 0);
	}
	glEnd();
}


- (void)rotate{
	log_debug(@"auto rotate");
	[_world.camera rotateX:-_rotateX];
	[_world.camera rotateY:-_rotateY];
	if(_rotateX){
		_rotateX += _auto_rotate_x * 5;
	}
	if(_rotateY){
		_rotateY += _auto_rotate_y * 5;
	}
	[_world.camera rotateX:_rotateX];
	[_world.camera rotateY:_rotateY];
	[self setNeedsDisplay:YES];
}

- (void)mouseMoved:(NSEvent *)event{
	static NSTimer *_rotateDetectTimer = nil;
	if(!_rotateDetectTimer){
		_rotateDetectTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 repeats:YES block:^(NSTimer * _Nonnull timer) {
			[self rotate];
		}];
		[_rotateDetectTimer setFireDate:[NSDate distantFuture]];
	}
	
	NSPoint pos = [event locationInWindow];
	pos = [self convertPoint:pos fromView:nil];
//	log_debug(@"%f %f", pos.x, pos.y);
	float dx, dy;
	float mx = self.bounds.size.width/2;
	float my = self.bounds.size.height/2;
	dx = pos.x - mx;
	dy = pos.y - my;
	
	if(fabs(dx) > self.bounds.size.width/2 - 20){
		_auto_rotate_y = (int)dx/fabs(dx);
	}else{
		_auto_rotate_y = 0;
	}
	if(fabs(dy) > self.bounds.size.height/2 - 20){
		_auto_rotate_x = (int)dy/fabs(dy);
	}else{
		_auto_rotate_x = 0;
	}
	if(_auto_rotate_x || _auto_rotate_y){
		log_debug(@"%f %f", _auto_rotate_y, _auto_rotate_x);
		[_rotateDetectTimer setFireDate:[NSDate date]];
		return;
	}else{
		[_rotateDetectTimer setFireDate:[NSDate distantFuture]];
	}
	
	dx = 90 * dx/(self.bounds.size.width/2);
	dy = 90 * dy/(self.bounds.size.height/2);
//	log_debug(@"%f %f", dx, dy);

	_world.camera.angle.x = -dy;
	_world.camera.angle.y = dx;


	[self setNeedsDisplay:YES];
	
//	log_debug(@"%f %f", dx, dy);
}

- (BOOL)acceptsFirstResponder{
	return YES;
}

- (void)keyDown:(NSEvent *)event{
	NSString *s = [event charactersIgnoringModifiers];
	if(!s || s.length == 0){
		return;
	}
	unichar c = [[event charactersIgnoringModifiers] characterAtIndex:0];
	float dx = 0;
	float dy = 0;
	float dz = 0;
	switch(c){
		case NSLeftArrowFunctionKey:{
			[_world.camera rotateY:-5];
			break;
		}
		case NSRightArrowFunctionKey:{
			[_world.camera rotateY:5];
			break;
		}
		case NSUpArrowFunctionKey:
			[_world.camera rotateX:5];
			break;
		case NSDownArrowFunctionKey:
			[_world.camera rotateX:-5];
			break;
		case 'a':
		case 'A':
			dx = -1;
			break;
		case 'd':
		case 'D':
			dx = 1;
			break;
		case 'w':
		case 'W':
			dz = 1;
			break;
		case 's':
		case 'S':
			dz = -1;
			break;
		default:
			return;
	}
	float speed = 50;
	dx *= speed;
	dz *= speed;
	dy *= speed;
	[_world.camera moveX:dx];
	[_world.camera moveY:dy];
	[_world.camera moveZ:dz];
//	log_debug(@"%f %f %f", dx, dy, dz);
	[self setNeedsDisplay:YES];
}
@end

