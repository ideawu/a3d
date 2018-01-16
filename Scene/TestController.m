//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "TestController.h"
#import <SceneKit/SceneKit.h>
#import <OpenGL/gl.h>
#import "Scene.h"
#import "a3d.h"

@interface TestController ()<NSWindowDelegate, SCNSceneRendererDelegate>{
	NSTimer *_timer;
}
@property Scene *scene1;
@property Scene *scene2;
@property SCNView *view;

@property SCNNode *photoNode;

//@property GLView *view;
@end

@implementation TestController

- (id)initWithWindowNibName:(NSNibName)windowNibName{
	self = [super initWithWindowNibName:windowNibName];
	self.window.delegate = self;
	
	CGRect frame = self.window.frame;
	frame.size = CGSizeMake(900, 600+(self.window.frame.size.height-self.window.contentView.bounds.size.height));
	[self.window setFrame:frame display:YES];
	
	NSDictionary *attr = @{
						   SCNPreferredRenderingAPIKey : @(SCNRenderingAPIOpenGLLegacy)
						   };
	_view = [[SCNView alloc] initWithFrame:self.window.contentView.bounds options:attr];
	[self.window.contentView addSubview:_view];
	[self setupScene];
	
	_view.showsStatistics = YES;
	_view.playing = YES;
	_view.scene = _scene1.scene;
	_view.delegate = self;

	log_debug(@"%@", _view.openGLContext.pixelFormat);
	
	
	return self;
}

- (IBAction)showWindow:(id)sender{
	[super showWindow:sender];
	
	log_debug(@"%s", __func__);
	[self render]; // 没有显示出来
}

- (void)windowDidResize:(NSNotification *)notification{
	log_debug(@"%s", __func__);
	_view.frame = self.window.contentView.bounds;
	[_scene1 setCameraWidth:_view.frame.size.width height:_view.frame.size.height depth:10000];
}

- (void)windowDidExpose:(NSNotification *)notification{
	log_debug(@"%s", __func__);
}

- (void)renderer:(id)renderer didRenderScene:(SCNScene *)scene atTime:(NSTimeInterval)time{
//	log_debug(@"%f", time);
//	log_debug(@"%@", _view.renderingAPI);
	glClear(GL_DEPTH_BUFFER_BIT);
	glLineWidth(1);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	{
		glVertex3f(-1, -1, 0);
		glVertex3f(1, 1, 0);
	}
	glEnd();
}


- (void)windowDidLoad {
    [super windowDidLoad];
	
	

	// TODO:
	_timer = [NSTimer scheduledTimerWithTimeInterval:0.03 repeats:YES block:^(NSTimer * timer) {
//		[self render];
	}];
}

- (void)setupScene{
	// 必须！
	[_view.openGLContext makeCurrentContext];

	_scene1 = [[Scene alloc] initWithViewportWidth:_view.frame.size.width height:_view.frame.size.height depth:1000];
	{
		SCNPlane *plane = [SCNPlane planeWithWidth:368 height:368];
		plane.firstMaterial.doubleSided = YES;
//		plane.firstMaterial.diffuse.contents = [SCNColor blueColor];
		plane.firstMaterial.diffuse.contents = @"/Users/ideawu/Downloads/imgs/9.jpg";
		_photoNode = [[SCNNode alloc] init];
		_photoNode.geometry = plane;
		_photoNode.position = SCNVector3Make(0, 0, 0);
		[_scene1 addNode:_photoNode];
	}
	
	_scene2 = [[Scene alloc] initWithViewportWidth:_view.frame.size.width height:_view.frame.size.height depth:1000];
	{
		SCNPlane *plane = [SCNPlane planeWithWidth:200 height:200];
		plane.firstMaterial.doubleSided = YES;
		plane.firstMaterial.diffuse.contents = [SCNColor blueColor];
		plane.firstMaterial.diffuse.contents = @"/Users/ideawu/Downloads/imgs/9.jpg";
		SCNNode *node = [SCNNode node];
		node.geometry = plane;
		node.position = SCNVector3Make(0, 0, -10);
		[_scene2 addNode:node];
	}
}

- (void)render{
	log_debug(@"");
	CGLLockContext(_view.openGLContext.CGLContextObj);
	[_view.openGLContext makeCurrentContext];
	[_view lockFocus];

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	_scene1.sceneTime += 0.05;
//	log_debug(@"%f", _scene1.sceneTime);
	glClear(GL_DEPTH_BUFFER_BIT);
	[_scene1 render];
	// 场景之间要 clear depth，因为两个场景的depth的比较没有意义
	glClear(GL_DEPTH_BUFFER_BIT);
	[_scene2 render];
	
	[_view unlockFocus];
	[_view.openGLContext flushBuffer];
	CGLUnlockContext(_view.openGLContext.CGLContextObj);
}

- (void)keyDown:(NSEvent *)event{
	NSString *s = [event charactersIgnoringModifiers];
	if(!s || s.length == 0){
		return;
	}
	unichar c = [[event charactersIgnoringModifiers] characterAtIndex:0];
	
	SCNVector3 pos = _photoNode.position;
	log_debug(@"%.2f %.2f %.2f", pos.x, pos.y, pos.z);
	switch(c){
		case NSLeftArrowFunctionKey:{
			SCNAction *move = [SCNAction moveTo:SCNVector3Make(pos.x-200, 0, 0) duration:1];
			move.timingMode = SCNActionTimingModeEaseOut;
			[_photoNode runAction:move];
			break;
		}
		case NSRightArrowFunctionKey:{
			SCNAction *move = [SCNAction moveTo:SCNVector3Make(pos.x+200, 0, 0) duration:1];
			move.timingMode = SCNActionTimingModeEaseOut;
			[_photoNode runAction:move];
			break;
		}
		case NSUpArrowFunctionKey:
			pos.y += 5;
			break;
		case NSDownArrowFunctionKey:
			pos.y -= 5;
			break;
	}
//	_photoNode.position = pos;
	[self render];
}
@end
