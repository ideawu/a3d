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
	GDraftSprite *_hero;
	GDraftSprite *_camera_hero;
	GAngle *_mouseAngle;
}
// 当前被控制的对象
@property GObject *currentObject;
@property NSMutableArray *objects;
@end

@implementation MyOpenGLView

- (void)prepareOpenGL {
	log_debug(@"%s", __func__);
	// 操作前务必要切换上下文
	[self.openGLContext makeCurrentContext];
	
	_mouseAngle = [[GAngle alloc] init];
	
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
		
		[_img1 moveX:400];
		[_img1 moveZ:500];
	}
	{
		NSString *filename = @"/Users/ideawu/Downloads/imgs/9.jpg";
		_img2 = [[GImage alloc] initWithContentsOfFile:filename];
		[_img2 moveX:_img2.width/2];
		[_img2 moveY:_img2.height/2];

		[_img2 moveX:2000];
		[_img2 moveZ:4000];
	}
	
	_hero = [[GDraftSprite alloc] init];
	_hero.width = 100;
	_hero.height = 100;
	_hero.depth = 100;
	_hero.color = GLKVector4Make(0.8, 0.8, 0.4, 1);
	[_hero moveX:200 y:_hero.height/2 z:200];

	_camera_hero = [[GDraftSprite alloc] init];
	_camera_hero.width = 100;
	_camera_hero.height = 100;
	_camera_hero.depth = 100;

	[_world.camera follow:_hero];

	_objects = [[NSMutableArray alloc] init];
	[_objects addObject:_world.camera];
	[_objects addObject:_hero];

	_currentObject = _world.camera;
}

- (void)switchSprite{
	int next = 0;
	for(int i=0; i<_objects.count; i++){
		GObject *obj = [_objects objectAtIndex:i];
		if(obj == _currentObject){
			next = (i + 1) % _objects.count;
			break;
		}
	}
	_currentObject = [_objects objectAtIndex:next];
//	[self resetMousePoint];
}

- (void)reshape {
	log_debug(@"%s", __func__);
	// 操作前务必要切换上下文
	[[self openGLContext] makeCurrentContext];
	log_debug(@"%.2f %.2f", self.bounds.size.width, self.bounds.size.height);
	[_world setCameraWidth:self.bounds.size.width height:self.bounds.size.height depth:self.bounds.size.width*20];
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
	[_hero render];
	
	_camera_hero.matrix = _world.camera.bodyMatrix;
	_camera_hero.angle = _world.camera.angle;
	[_camera_hero moveX:0 y:-(_world.camera.height/2)+_camera_hero.height/2 z:50];
	[_camera_hero render];
	
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
	glDisable(GL_LINE_STIPPLE);
}


- (void)mouseMoved:(NSEvent *)event{
	[super mouseMoved:event];
	
	float dx = 90 * self.mouseTranslate.x/(self.bounds.size.width/2);
	float dy = 90 * self.mouseTranslate.y/(self.bounds.size.height/2);
	float ax = -dy;
	float ay = dx;
//	log_debug(@"%f %f", ax, ay);

	_currentObject.angle.x = ax;
	_currentObject.angle.y = ay;
	
	if(_currentObject == _camera_hero){
		_rotateX = (fabs(ax) < 80)? 0 : ax/fabs(ax) * 2;
		_rotateY = (fabs(ay) < 80)? 0 : ay/fabs(ay) * 2;
		static NSTimer *_rotateDetectTimer = nil;
		if(_rotateX || _rotateY){
			if(!_rotateDetectTimer){
				_rotateDetectTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 repeats:YES block:^(NSTimer * _Nonnull timer) {
					[self rotate];
				}];
			}
			[_rotateDetectTimer setFireDate:[NSDate date]];
		}else{
			[_rotateDetectTimer setFireDate:[NSDate distantFuture]];
		}
	}

	[self setNeedsDisplay:YES];
	
//	log_debug(@"%f %f", dx, dy);
}

- (void)rotate{
	log_debug(@"auto rotate %.2f, %.2f", _rotateX, _rotateY);
	// 注意先后顺序
	[_world.camera rotateY:_rotateY];
	[_world.camera rotateX:_rotateX];
	[self setNeedsDisplay:YES];
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
		case ' ':{
			// 切换被控制角色
			[self switchSprite];
			break;
		}
		case NSLeftArrowFunctionKey:{
			[_currentObject rotateY:-5];
			break;
		}
		case NSRightArrowFunctionKey:{
			[_currentObject rotateY:5];
			break;
		}
		case NSUpArrowFunctionKey:
			[_currentObject rotateX:5];
			break;
		case NSDownArrowFunctionKey:
			[_currentObject rotateX:-5];
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
	[_currentObject moveX:dx];
	[_currentObject moveY:dy];
	[_currentObject moveZ:dz];
//	log_debug(@"%f %f %f", dx, dy, dz);
	[self setNeedsDisplay:YES];
}
@end

