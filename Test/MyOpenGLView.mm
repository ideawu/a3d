#import "MyOpenGLView.h"
#import <GLKit/GLKit.h>
#import "MySprite.h"
#import "GDraftSprite.h"


#include "a3d/Context.h"
#include "a3d/Camera.h"
#include "a3d/DraftScene.h"

@interface MyOpenGLView(){
	GImage *_img1;
	GImage *_img2;
	float _rotateX;
	float _rotateY;
	int _auto_rotate_x;
	int _auto_rotate_y;
	GDraftSprite *_flag;
	GDraftSprite *_camera_hero;
	MySprite *_hero;
	GCamera *_fakeCamera;
	
	a3d::Camera *_camera;
	a3d::Context *_context;
	
	DraftScene *_scene;

}
// 当前被控制的对象
@property GObject *currentObject;
@property NSMutableArray *objects;
@end

@implementation MyOpenGLView

- (void)prepareOpenGL {
	// 操作前务必要切换上下文
	[self.openGLContext makeCurrentContext];
	
	_camera = NULL;
	_context = NULL;
	
	_rotateX = 0;
	_rotateY = 0;

	_scene = new DraftScene();
	_scene->width(10000);
	_scene->height(10000);
	_scene->depth(10000);
	
//	[_scene moveX:200 y:200 z:5];

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
	
	_flag = [[GDraftSprite alloc] init];
	_flag.width = 100;
	_flag.height = 100;
	_flag.depth = 100;
	_flag.color = GLKVector4Make(0.8, 0.8, 0.4, 1);
//	[_flag moveX:200 y:_flag.height/2 z:200];

	_hero = [[MySprite alloc] init];
	[_hero moveX:800 y:0 z:800];
//	[_hero rotateZ:30];

	_fakeCamera = [[GCamera alloc] init];
	[_fakeCamera moveX:_hero.x-120 y:_hero.y+200 z:_hero.z-300];
	[_fakeCamera follow:_hero];

	_objects = [[NSMutableArray alloc] init];
	[_objects addObject:_hero];
	[_objects addObject:_fakeCamera];

	_currentObject = _hero;
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
	// 操作前务必要切换上下文
	[[self openGLContext] makeCurrentContext];
	
	float width = self.bounds.size.width;
	float height = self.bounds.size.height;
	float depth = width * 20;
	
	delete _camera;
	delete _context;
	_camera = a3d::Camera::create(60, width, height, depth);
	_context = a3d::Context::memoryContext(width, height);
}

- (void)drawRect:(NSRect)aRect {
	// 操作前务必要切换上下文
	[[self openGLContext] makeCurrentContext];
	
	_context->bind();
	_context->clear(0, 0, 0, 1);
	_context->setupCamera3D(_camera);
	[self draw3D];
	_context->setupCamera2D(_camera);
	[self draw2D];
	_context->finish();

	[[self openGLContext] flushBuffer];
}

- (void)draw3D{
	[_img1 render];
	[_img2 render];
	[_hero render];

	_flag.matrix = _fakeCamera.matrix;
	[_flag render];
	
	_scene->render();
}

- (void)draw2D{
	float width = self.bounds.size.width;
	float height = self.bounds.size.height;
	float len = 10;
	float x0 = width/2 - len;
	float y0 = height/2 - len;
	float x1 = width/2 + len;
	float y1 = height/2 + len;

//	glEnable(GL_LINE_STIPPLE);
//	glLineStipple(1, 0x0f0f);
	glLineWidth(1);
	
	glColor4f(0, 1, 0, 1);
	glBegin(GL_LINES);
	{
		glVertex3f(x0, height/2, 0);
		glVertex3f(x1, height/2, 0);
		glVertex3f(width/2, y0, 0);
		glVertex3f(width/2, y1, 0);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

- (void)mouseUp:(NSEvent *)event{
//	GObject *target = _hero;
//	GRay *ray = [_world.camera rayFromScreenPointX:self.mousePoint.x y:self.mousePoint.y];
//	GLKVector3 pos = [ray nearestPointTo:target.pos];
//	log_debug(@"%.2f %.2f %.2f", pos.x, pos.y, pos.z);
//	pos = mat4_mul_vec3(mat4_invert(target.matrix), pos);
//	log_debug(@"%.2f %.2f %.2f", pos.x, pos.y, pos.z);
	
	
//	GLKVector3 force = GLKVector3Make(0, 0, 1);
//	force = GLKMatrix4MultiplyVector3(GLKMatrix4Invert(target.matrix, NULL), force);
//	force = GLKVector3MultiplyScalar(force, 10);
//	// 将力转成被控对象坐标系内
//	[target force:force atPoint:pos rotationScalar:1];
	[self setNeedsDisplay:YES];
}

- (void)mouseMoved:(NSEvent *)event{
	[super mouseMoved:event];
//	log_debug(@"ignore mouse");
	return;
	
	float dx = 90 * self.mouseTranslate.x/(self.bounds.size.width/2);
	float dy = 90 * self.mouseTranslate.y/(self.bounds.size.height/2);
	float ax = -dy;
	float ay = dx;
	log_debug(@"%.2f %.2f", ax, ay);

	_currentObject.angle.yaw = ay;
	_currentObject.angle.pitch = ax;
//	log_debug(@"%@", _currentObject.angle);
	
//	if(_currentObject == _camera_hero){
		_rotateX = (fabs(ax) < 70)? 0 : ax/fabs(ax) * 1;
		_rotateY = (fabs(ay) < 70)? 0 : ay/fabs(ay) * 1;
		static NSTimer *_rotateDetectTimer = nil;
		if(_rotateX || _rotateY){
			if(!_rotateDetectTimer){
				_rotateDetectTimer = [NSTimer scheduledTimerWithTimeInterval:0.01 repeats:YES block:^(NSTimer * _Nonnull timer) {
					[self rotate];
				}];
			}
			[_rotateDetectTimer setFireDate:[NSDate date]];
		}else{
			[_rotateDetectTimer setFireDate:[NSDate distantFuture]];
		}
//	}

	[self setNeedsDisplay:YES];
	
//	log_debug(@"%f %f", dx, dy);
}

- (void)rotate{
	log_debug(@"auto rotate %.2f, %.2f", _rotateX, _rotateY);
	// 注意先后顺序
	[_currentObject rotateY:_rotateY];
	[_currentObject rotateX:_rotateX];
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
		case '[':{
			[_currentObject rotateZ:10];
			break;
		}
		case ']':{
			[_currentObject rotateZ:-10];
			break;
		}
		case NSLeftArrowFunctionKey:{
			[_currentObject rotateY:-10];
			break;
		}
		case NSRightArrowFunctionKey:{
			[_currentObject rotateY:10];
			break;
		}
		case NSUpArrowFunctionKey:
			[_currentObject rotateX:10];
			break;
		case NSDownArrowFunctionKey:
			[_currentObject rotateX:-10];
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
		case 'f':
		case 'F':{
//			if(_world.camera.follow){
//				log_debug(@"unfollow");
//				[_world.camera unfollow];
//			}else{
//				log_debug(@"follow");
//				[_world.camera follow:_hero];
//			}
			break;
		}
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

	[GEulerAngle angleWithMatrix:_currentObject];
//	log_debug(@"%@", [GEulerAngle angleWithMatrix:_currentObject]);
	
	[self setNeedsDisplay:YES];
}
@end

