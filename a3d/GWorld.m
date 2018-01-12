//  Created by ideawu on 28/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GWorld.h"
#import "GFrame.h"

@interface GWorld(){
	BOOL _offscreenEnabled;
	// 世界矩阵一般包含坐标定义，投影信息。而通过改变相机矩阵来达到空间变化效果。
	NSMutableArray *_nodes3d;
}
@property GFrame *frame;
@end

@implementation GWorld

- (id)init{
	self = [super init];
	_offscreenEnabled = YES;
	
	_camera = [[GCamera alloc] init];
	_camera.fovy = 60;
	
	_nodes3d = [[NSMutableArray alloc] init];
	return self;
}

- (void)enableOffscreenBuffer{
	_offscreenEnabled = YES;
	if(_camera.width > 0 && _camera.height > 0){
		[self setupFrameBuffer];
	}
}

- (void)disableOffscreenBuffer{
	_offscreenEnabled = NO;
	_frame = nil;
}

- (void)setupFrameBuffer{
	_frame = [[GFrame alloc] initWithWidth:_camera.width height:_camera.height];
}

- (void)setCameraFovy:(float)fovy width:(float)width height:(float)height depth:(float)depth{
	BOOL isNew2d = NO;
	if(width != _camera.width || height != _camera.height){
		isNew2d = YES;
	}
	BOOL isNew3d = NO;
	if(isNew2d || fovy != _camera.fovy || depth != _camera.depth){
		isNew3d = YES;
	}
	
	_camera.fovy = fovy;
	_camera.width = width;
	_camera.height = height;
	_camera.depth = depth;
//	[_camera moveX:width/2];
//	[_camera moveY:height/2];

	if(isNew2d){
		[self setupFrameBuffer];
	}
	if(isNew3d){
		[self setupCamera];
	}
}

- (void)setCameraWidth:(float)width height:(float)height depth:(float)depth{
	[self setCameraFovy:_camera.fovy width:width height:height depth:depth];
}

- (void)setupCamera{
	[_camera setup];
}

- (void)beginRender{
	if(_offscreenEnabled){
		[_frame bind];
	}

	// 设置背景色
//	glClearColor(1, 1, 1, 1);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

- (void)render3D{
	[self bind3D];
	[self draw3D];
}

- (void)render2D{
	[self bind2D];
	[self draw2D];
}

- (void)finishRender{
	if(_offscreenEnabled){
		[_frame flush];
	}
	glFinish();
}

- (void)bind3D{
	[_camera bind3D];
}

- (void)bind2D{
	[_camera bind2D];
}

- (void)draw3D{
}

- (void)draw2D{
}


- (void)addNode:(GNode *)node{
	[_nodes3d addObject:node];
}

@end
