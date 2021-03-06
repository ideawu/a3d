#import "MyOpenGLView.h"
#import "MySprite.h"

#include "a3d/DraftScene.h"
#include "a3d/DraftSprite.h"
#include "a3d/a3d.h"

using namespace a3d;

@interface MyOpenGLView(){
	float _rotateX;
	float _rotateY;
	int _auto_rotate_x;
	int _auto_rotate_y;
	
	Context *_context;
	Drawable *_drawable;
	Camera *_camera;

	DraftScene *_scene;
	DraftSprite *_flag;
	DraftSprite *_camera_alex;
	SpriteNode *_img1;
	SpriteNode *_img2;
	SpriteNode *_text;

	MySprite *_alex;

	std::vector<a3d::Node*> _objects;
}
// 当前被控制的对象
@property a3d::Node *currentObject;
@end

@implementation MyOpenGLView

- (void)dealloc{
	log_debug(@"%s", __func__);
}

- (void)setup{
	log_debug(@"%s", __func__);
	[self showStatistics];
//	[self setAcceptsTouchEvents:YES];

	_context = a3d::Context::createShared();
	_camera = a3d::Camera::create();

	_rotateX = 0;
	_rotateY = 0;

	_scene = new DraftScene();
	_scene->width(10000);
	_scene->height(10000);
	_scene->depth(10000);
	
//	[_scene moveX:200 y:200 z:5];

	_alex = new MySprite();
	_alex->move(500, 0, 200);

	SpriteNode *node;
	{
		node = new SpriteNode();
//		Sprite *sprite = Sprite::imageSprite("/Users/ideawu/Downloads/camera.jpg");
//		node->sprite(sprite);
//		node->move(node->width()/2, node->height()/2, 0);
		node->move(self.viewportSize.width/4, self.viewportSize.height/2, 0);
		node->scale(0.2);
//		node->rotateY(50);
		_img1 = node;
	}
	{
		node = new SpriteNode();
		Sprite *sprite = Sprite::imageSprite("/Users/wuzuyang/Downloads/bg1.png");
		node->sprite(sprite);
//		node->move(node->width()/2, node->height()/2, 0);
		node->move(0, 0, 1);
		_img2 = node;
	}
	{
		node = new SpriteNode();
		Sprite *sprite = Sprite::textSprite("Hello World! 你好！", 50, Color::yellow());
		node->sprite(sprite);
		node->move(node->width()/2, node->height()/2, 0);
		node->opacity(0.9);
		_text = node;

		_text->move(450, 150, 0);
		
//		_text->move(-50, 0, -20);
//		_alex->addSubnode(_text);
//		_alex->clipBounds(YES);
	}
	
	_flag = new DraftSprite();
	_flag->width(100);
	_flag->height(100);
	_flag->depth(100);
	
	_objects.push_back(_alex);
	_objects.push_back(_camera);

	_currentObject = _alex;
}

- (void)resize{
	delete _drawable;
	_drawable = a3d::Drawable::create(self.framebufferSize.width, self.framebufferSize.height, 4);

	CGSize size = [NSScreen mainScreen].frame.size;
	size = self.viewportSize;
	float width = size.width/1;
	float height = size.height/1;
	float depth = fmax(width, height) * 10;
	log_debug(@"%.0f %.0f", width, self.framebufferSize.width);

	_camera->setup(60, width, height, depth, -200);
	_camera->position(width/2, height/2, 0);
}

- (void)renderAtTime:(double)time{
	// 当前的 FBO 不一定是 0
	GLint drawFboId = 0, readFboId = 0;
	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
	glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

	_context->makeCurrent();
	_drawable->begin();
	_drawable->clear(0.1, 0.1, 0.1);

	{
		CGSize size = CGSizeMake(_camera->width(), _camera->height());
		size = [self convertSizeToBacking:size];
//		glViewport(0, 0, size.width, size.height);
	}
	{ // 在 10.13 会有导致在窗口resize时 view 更新即时
//		CGSize size = self.frame.size;
//		size = [self convertSizeToBacking:size];
//		log_debug(@"%.2f %.2f", size.width/2, size.height/2);
//		glEnable(GL_SCISSOR_TEST);
//		glScissor(0, 0, size.width, size.height);
	}

	_camera->view3D();
	[self draw3D];

	_scene->renderAtTime(time);
	_camera->renderAtTime(time);

	_alex->renderAtTime(time);
	if(!_text->parent()){
		_text->renderAtTime(time);
	}

	_flag->renderAtTime(time);
	_img1->renderAtTime(time);
//	_img2->renderAtTime(time);

	_camera->view2D();
	[self draw2D];
	
	_drawable->blit(drawFboId);
	// 不需要调用 finish
//	_drawable->finish();
}

- (void)draw3D{
	glColor4f(0, 1, 0, 1);
	glLineWidth(2);
	glBegin(GL_LINES);
	{
		glVertex3f(0, 0, 0);
		glVertex3f(500, 0, 0);
	}
	glEnd();
	for(int i=0; i<1200; i+=100){
	glBegin(GL_LINES);
	{
		glVertex3f(i, 500, -00);
		glVertex3f(i, 500, 20000);
	}
	glEnd();
	}
}

- (void)draw2D{
	float width = self.viewportSize.width;
	float height = self.viewportSize.height;
	float len = 10;
//	width = 50;
//	height = 50;
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

- (void)swipeWithEvent:(NSEvent *)event {
	log_debug(@"%s", __func__);
}

- (void)magnifyWithEvent:(NSEvent *)event {
	log_debug(@"%s", __func__);
}

- (void)rotateWithEvent:(NSEvent *)event {
	log_debug(@"%s", __func__);
}

- (void)scrollWheel:(NSEvent *)event{
	float sx = event.scrollingDeltaX;
	float dx = event.deltaX;
	float sx2 = copysign(pow(fabs(sx), 1.0/2), sx);
	float x = sx2;
	if(sx + dx != 0){
		if(event.momentumPhase){
			return;
		}
		log_debug(@"sx: %.2f, sx2: %.2f, dx: %.2f", sx, sx2, dx);
		_alex->move(-x, 0, 0);
	}
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
		case '0':{
			_alex->position(0, 0, 0);
			break;
		}
		case 'q':{
			[self.window close];
			return;
		}
		case 'f':{
			[self.window zoom:nil];
			break;
		}
		case 'c':{
			// 切换被控制角色
			[self switchSprite];
			break;
		}
		case ' ':{
//			Node *node = _text;
//			node = _currentObject;
			Node *node = _alex;

			a3d::Axis axis = a3d::Axis(a3d::Point3(500, 0, 800), a3d::Point3(500, 300, 800));
			axis = node->convertAxisFromWorld(axis);

			{
				a3d::Animate *action = a3d::Animate::move(0, -80, 0);
				action->easingFunc(a3d::TimingFuncEaseIn);
//				action->repeats(2);
				action->bounceFunc(a3d::TimingFuncEaseOut);
				action->bounce(7);
//				action->accelateFunc(a3d::TimingFuncLinear);
				action->duration(0.5 * (action->bounce() + 1));
				node->runAnimation(action);
			}
			{
				a3d::Animate *action = a3d::Animate::rotate(360, Vector3(0, 1, 0));
				action->easingFunc(a3d::TimingFuncLinear);
				action->loop(true);
				action->duration(5);
				node->runAnimation(action);
			}
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
//			log_debug(@"");
			a3d::Animate *action = a3d::Animate::rotate(60, Vector3(0, 0, 1));
			action->easingFunc(a3d::TimingFuncLinear);
			action->duration(1);
			_currentObject->runAnimation(action);
			break;
		}
		case NSRightArrowFunctionKey:{
//			log_debug(@"");
			a3d::Animate *action = a3d::Animate::rotate(-60, Vector3(0, 0, 1));
			action->easingFunc(a3d::TimingFuncLinear);
			action->duration(1);
			_currentObject->runAnimation(action);
			break;
		}
		case NSUpArrowFunctionKey:
			_currentObject->rotateX(30);
			break;
		case NSDownArrowFunctionKey:
			_currentObject->rotateX(-30);
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
	float speed = 5;
	dx *= speed;
	dz *= speed;
	dy *= speed;
	_camera->move(dx, dy, dz);
//	log_debug(@"%f %f %f", _currentObject->x(), _currentObject->y(), _currentObject->z());

//	[GEulerAngle angleWithMatrix:_currentObject];
//	log_debug(@"%@", [GEulerAngle angleWithMatrix:_currentObject]);
}
@end

