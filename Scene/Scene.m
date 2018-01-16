//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "Scene.h"
#import <OpenGL/gl3.h>

@interface Scene(){
}
@property (readonly) SCNCamera *camera;
@property SCNNode *cameraNode;
@property SCNRenderer *renderer;
@end


@implementation Scene

- (void)setCameraWidth:(float)width height:(float)height depth:(float)depth{
	// 将视口设置为渲染目标的大小，这样，在原点位置的物体投影后体积不变。
	_camera.zNear = (height/2)/tan(M_PI/180 * (_camera.fieldOfView/2));
	//	log_debug(@"%f %f %f %f %f", _camera.fieldOfView, _camera.zNear, width, height, depth);
	_camera.zFar = _camera.zNear + depth;
	_cameraNode.position = SCNVector3Make(0, 0, _camera.zNear+0.0001);
//	glViewport(0, 0, (int)width, (int)height);
}

- (id)initWithViewportWidth:(float)width height:(float)height depth:(float)depth{
	self = [super init];
	_scene = [SCNScene scene];
	_scene.background.contents = [SCNColor whiteColor];

	_camera = [SCNCamera camera];
	// 将视口设置为渲染目标的大小，这样，在原点位置的物体投影后体积不变。
	_camera.zNear = (height/2)/tan(M_PI*2 * (_camera.fieldOfView/2/360));
	//log_debug(@"%f %f %f %f %f", _camera.fieldOfView, _camera.zNear, width, height, depth);
	_camera.zFar = _camera.zNear + depth;

	_cameraNode = [SCNNode node];
	_cameraNode.camera = _camera;
	_cameraNode.position = SCNVector3Make(0, 0, _camera.zNear+0.001);
	[_scene.rootNode addChildNode:_cameraNode];
	
//	CGLContextObj ctx = [NSOpenGLContext currentContext].CGLContextObj;
//	_renderer = [SCNRenderer rendererWithContext:ctx options:nil];
////	_renderer.autoenablesDefaultLighting = YES;
////	_renderer.pointOfView = _cameraNode; // not necessary
////	_renderer.showsStatistics = YES;
//	_renderer.playing = YES;
//
//	_renderer.scene = _scene;
	
	return self;
}

- (void)addNode:(SCNNode *)node{
	[_scene.rootNode addChildNode:node];
}

- (void)render{
	[_renderer renderAtTime:self.sceneTime];
}

@end
