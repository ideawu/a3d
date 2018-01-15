//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "TestController.h"
#import <SceneKit/SceneKit.h>

@interface TestController ()
@property SCNView *view;
@property SCNScene *scene;
@property SCNCamera *camera;
@property SCNNode *lightNode;
@property SCNNode *cameraNode;
@end

@implementation TestController

- (void)windowDidLoad {
    [super windowDidLoad];
	
	CGRect frame = self.window.frame;
	frame.size = CGSizeMake(900, 600+(self.window.frame.size.height-self.window.contentView.bounds.size.height));
	[self.window setFrame:frame display:YES];

	_view = [[SCNView alloc] initWithFrame:self.window.contentView.bounds];
//	log_debug(@"%@", NSStringFromRect(_view.frame));
	_view.allowsCameraControl = YES;
	_view.showsStatistics = YES;
	_view.backgroundColor = [SCNColor blackColor];
	[self.window.contentView addSubview:_view];

	_scene = [[SCNScene alloc] init];
	_camera = [SCNCamera camera];
	_camera.zFar = 2000;
	// 将视口设置为渲染目标的大小，这样，在原点位置的物体投影后体积不变。
	_camera.zNear = (_view.frame.size.height/2)/tan(M_PI*2 * (_camera.fieldOfView/2/360));
//	log_debug(@"%f %f %f", _camera.fieldOfView, _camera.focalLength, _camera.zNear);
	
	_lightNode = [SCNNode node];
	_lightNode.name = @"light";
	_lightNode.light = [SCNLight light];
	_lightNode.light.type = SCNLightTypeAmbient;
	_lightNode.light.color = [NSColor blackColor];
	//	[_scene.rootNode addChildNode:_lightNode];

	_cameraNode = [[SCNNode alloc] init];
	_cameraNode.name = @"camera";
	_cameraNode.camera = _camera;
	_cameraNode.position = SCNVector3Make(0, 0, _camera.zNear+0.1);
	[_scene.rootNode addChildNode:_cameraNode];
	
	SCNPlane *plane = [SCNPlane planeWithWidth:400 height:300];
	plane.firstMaterial.doubleSided = YES;
//	plane.firstMaterial.diffuse.contents = @"/Users/ideawu/Downloads/imgs/1.jpg";
	SCNNode *node = [[SCNNode alloc] init];
	node.geometry = plane;
	node.position = SCNVector3Make(0, 0, 0);
	[_scene.rootNode addChildNode:node];

	_view.scene = _scene;
}

@end
