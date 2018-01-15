//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "TestController.h"
#import <SceneKit/SceneKit.h>
#import <OpenGL/gl.h>
#import "Scene.h"
#import "a3d.h"

@interface TestController (){
	NSTimer *_timer;
}
@property Scene *scene1;
@property Scene *scene2;

@property SCNNode *photoNode;

@property GLView *view;
@end

@implementation TestController

- (void)windowDidLoad {
    [super windowDidLoad];
	
	CGRect frame = self.window.frame;
	frame.size = CGSizeMake(900, 600+(self.window.frame.size.height-self.window.contentView.bounds.size.height));
	[self.window setFrame:frame display:YES];

	_view = [[GLView alloc] initWithFrame:self.window.contentView.bounds];
	[self.window.contentView addSubview:_view];
	
	[self setupScene];
//	[self render]; // 没有显示出来
	
	// TODO:
	_timer = [NSTimer scheduledTimerWithTimeInterval:0.03 repeats:YES block:^(NSTimer * timer) {
		[self render];
	}];
}

- (void)setupScene{
	// 必须！
	[_view.openGLContext makeCurrentContext];

	_scene1 = [[Scene alloc] initWithViewportWidth:_view.frame.size.width height:_view.frame.size.height depth:1000];
	{
		SCNPlane *plane = [SCNPlane planeWithWidth:400 height:300];
		plane.firstMaterial.doubleSided = YES;
		plane.firstMaterial.diffuse.contents = [SCNColor blueColor];
		plane.firstMaterial.diffuse.contents = @"/Users/ideawu/Downloads/imgs/3.jpg";
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
	[_view lockFocus];
	[_view.openGLContext makeCurrentContext];

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
	
	[_view.openGLContext flushBuffer];
	[_view unlockFocus];
	[_view setNeedsDisplay:YES];
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
