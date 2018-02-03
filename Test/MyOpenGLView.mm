#import "MyOpenGLView.h"
#import "MySprite.h"

#include <vector>
#include "a3d/DraftScene.h"
#include "a3d/DraftSprite.h"
#include "a3d/a3d.h"

@interface MyOpenGLView(){
	float _rotateX;
	float _rotateY;
	int _auto_rotate_x;
	int _auto_rotate_y;
	
	a3d::Camera *_camera;
	a3d::Context *_context;
	
	DraftScene *_scene;
	DraftSprite *_flag;
	DraftSprite *_camera_hero;
	a3d::SpriteNode *_img1;
	a3d::SpriteNode *_img2;

	MySprite *_hero;

	std::vector<a3d::Object *> _objects;
}
// 当前被控制的对象
@property a3d::Object *currentObject;
@end

@implementation MyOpenGLView

- (void)prepareOpenGL {
	[super prepareOpenGL];

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
		_img1 = new a3d::SpriteNode();
		a3d::Sprite *sprite = a3d::Sprite::imageSprite("/Users/ideawu/Downloads/imgs/9.jpg");
		_img1->sprite(sprite);
		_img1->move(_img1->width()/2, _img1->height()/2, 0);
		_img1->move(100, 0, 300);
		_img1->opacity(0.8);
	}
	{
		_img2 = new a3d::SpriteNode();
		a3d::Sprite *sprite = a3d::Sprite::imageSprite("/Users/ideawu/Downloads/imgs/1.jpg");
		_img2->sprite(sprite);
		_img2->move(_img2->width()/2, _img2->height()/2, 0);
		_img2->move(100, 0, 300);
		_img2->opacity(0.7);
	}
	
	_flag = new DraftSprite();
	_flag->width(100);
	_flag->height(100);
	_flag->depth(100);

//	_flag.color = GLKVector4Make(0.8, 0.8, 0.4, 1);
//	[_flag moveX:200 y:_flag.height/2 z:200];

	_hero = new MySprite();
	_hero->move(800, 0, 800);

	_objects.push_back(_hero);
	_objects.push_back(_camera);

	_currentObject = _hero;
	
	[self startAnimation];
}

- (void)switchSprite{
	int next = 0;
	for(int i=0; i<_objects.size(); i++){
		a3d::Object *obj = _objects[i];
		if(obj == _currentObject){
			next = (i + 1) % _objects.size();
			break;
		}
	}
	_currentObject = _objects[next];
//	[self resetMousePoint];
}

- (void)reshape {
	// 操作前务必要切换上下文
	[[self openGLContext] makeCurrentContext];
	
	float width = self.viewportSize.width;
	float height = self.viewportSize.height;
	float depth = width * 20;

	if(!_camera){
		_camera = a3d::Camera::create(60, width, height, depth);
		_camera->position(width/2, height/2, 0);
	}else{
		_camera->setup(60, width, height, depth);
	}

	delete _context;
	_context = a3d::Context::bufferContext(self.framebufferSize.width, self.framebufferSize.height);

	_objects.pop_back();
	_objects.push_back(_camera);
}

- (void)drawRect:(NSRect)dirtyRect{
	[self renderAtTime:0];
}

- (void)renderAtTime:(double)time{
//	log_debug(@"");
	[[self openGLContext] makeCurrentContext];
	
	_context->begin();
	_context->clear(0, 0, 0, 1);
	_context->loadMatrix3D(_camera->matrix3D());
	[self draw3D];
	_hero->renderAtTime(time);
	_context->loadMatrix2D(_camera->matrix2D());
	[self draw2D];
	_context->blit();
	
	
	[[self openGLContext] flushBuffer];
}

- (void)draw3D{
	_scene->render();
	_flag->render();
//	_img1->render();
//	_img2->render();
	
	//	a3d::Axis axis = a3d::Axis(a3d::Vector3(10, 100, 100), a3d::Vector3(10,100,50));
	glLineWidth(1);
	glBegin(GL_LINES);
	{
		glVertex3f(500, 0, 800);
		glVertex3f(500, 400, 800);
	}
	glEnd();
	
	_hero->render();
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
	
//	float dx = 90 * self.mouseTranslate.x/(self.bounds.size.width/2);
//	float dy = 90 * self.mouseTranslate.y/(self.bounds.size.height/2);
//	float ax = -dy;
//	float ay = dx;
//	log_debug(@"%.2f %.2f", ax, ay);
//
////	_currentObject.angle.yaw = ay;
////	_currentObject.angle.pitch = ax;
////	log_debug(@"%@", _currentObject.angle);
//
////	if(_currentObject == _camera_hero){
//		_rotateX = (fabs(ax) < 70)? 0 : ax/fabs(ax) * 1;
//		_rotateY = (fabs(ay) < 70)? 0 : ay/fabs(ay) * 1;
//		static NSTimer *_rotateDetectTimer = nil;
//		if(_rotateX || _rotateY){
//			if(!_rotateDetectTimer){
//				_rotateDetectTimer = [NSTimer scheduledTimerWithTimeInterval:0.01 repeats:YES block:^(NSTimer * _Nonnull timer) {
//					[self rotate];
//				}];
//			}
//			[_rotateDetectTimer setFireDate:[NSDate date]];
//		}else{
//			[_rotateDetectTimer setFireDate:[NSDate distantFuture]];
//		}
////	}
//
//	[self setNeedsDisplay:YES];
	
//	log_debug(@"%f %f", dx, dy);
}

- (void)rotate{
//	log_debug(@"auto rotate %.2f, %.2f", _rotateX, _rotateY);
//	// 注意先后顺序
//	[_currentObject rotateY:_rotateY];
//	[_currentObject rotateX:_rotateX];
//	[self setNeedsDisplay:YES];
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
		case '3':{
			[self stopAnimation];
			break;
		}
		case '4':{
			[self startAnimation];
			break;
		}
		case ' ':{
			// 切换被控制角色
//			[self switchSprite];
			
			a3d::Axis axis = a3d::Axis(a3d::Point3(500, 0, 800), a3d::Point3(500, 200, 800));
			axis = _hero->convertAxisFromWorld(axis);
			a3d::Animate *action = a3d::Animate::rotate(90, axis);
//			a3d::Animate *action = a3d::Animate::rotate(90, a3d::Vector3(0,1,0));
//			a3d::Animate *action = a3d::Animate::move(a3d::Vector3(100, 0, 0), 1);
			action->easingFunc(a3d::TimingFuncLoop);
			action->bounceFunc(a3d::TimingFuncLinear);
			action->accelateFunc(a3d::TimingFuncLinear);
			action->bounce(10);
			action->duration(1 * action->bounce());
			_hero->runAnimation(action);
			break;
		}
		case '[':{
			_currentObject->rotateZ(10);
			break;
		}
		case ']':{
			_currentObject->rotateZ(-10);
			break;
		}
		case NSLeftArrowFunctionKey:{
			_currentObject->rotateY(-10);
			break;
		}
		case NSRightArrowFunctionKey:{
			_currentObject->rotateY(10);
			break;
		}
		case NSUpArrowFunctionKey:
			_currentObject->rotateX(10);
			break;
		case NSDownArrowFunctionKey:
			_currentObject->rotateX(-10);
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
		case '1':{
			a3d::Animate *action = a3d::Animate::move(a3d::Vector3(100, 0, 0), 1);
			_hero->runAnimation(action);
			break;
		}
		case '2':{
			static double time = 0;
			time += 0.1;
			_hero->renderAtTime(time);
			[self setNeedsDisplay:YES];
		}
		default:
			return;
	}
	float speed = 5;
	dx *= speed;
	dz *= speed;
	dy *= speed;
	_currentObject->move(dx, dy, dz);
//	log_debug(@"%f %f %f", _currentObject->x(), _currentObject->y(), _currentObject->z());

//	[GEulerAngle angleWithMatrix:_currentObject];
//	log_debug(@"%@", [GEulerAngle angleWithMatrix:_currentObject]);
}
@end

