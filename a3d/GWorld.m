//  Created by ideawu on 28/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GWorld.h"
#import "GFrame.h"

@interface GWorld(){
	BOOL _offscreenEnabled;
	// 世界矩阵一般包含坐标定义，投影信息。而通过改变相机矩阵来达到空间变化效果。
	GLKMatrix4 _matrix3d;
	GLKMatrix4 _matrix2d;
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
	// 将原点坐标移到屏幕右下角
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
	float width = _camera.width;
	float height = _camera.height;
	float near = (height/2) / tan(GLKMathDegreesToRadians(_camera.fovy/2));
	float far = near + _camera.depth;

	glViewport(0, 0, width, height);
	
	// 将前裁剪面设置为与viewport同大小
	_matrix3d = GLKMatrix4MakeFrustum(-width/2, width/2, -height/2, height/2, near, far);
	// 将前裁剪面后移，因为视点默认在 (0,0,0)，所以默认前裁剪面在(near,0,0)，这在旋转物体时不方便
	_matrix3d = GLKMatrix4Translate(_matrix3d, 0, 0, -near);
	// 翻转z轴，将z轴方向和人看屏幕方向相同
	_matrix3d = GLKMatrix4Scale(_matrix3d, 1, 1, -1);
	// 应该移动相机，而不是移动世界
	_matrix3d = GLKMatrix4Translate(_matrix3d, -width/2, -height/2, 0);

	// OpenGL 的老方式
	//	glLoadIdentity();
	//	glFrustum(-width/2, width/2, -height/2, height/2, near, far);
	//	glTranslatef(0, 0, -near);
	//	glScalef(1, 1, -1);
	
	_matrix2d = GLKMatrix4MakeOrtho(-width/2, width/2, -height/2, height/2, -far, far);
	// 翻转y轴，y轴方向向下
	_matrix2d = GLKMatrix4Scale(_matrix2d, 1, -1, -1);
	// 将原点坐标移到屏幕左上角
	_matrix2d = GLKMatrix4Translate(_matrix2d, -width/2, -height/2, 0);
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
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat *)&_matrix3d);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 相机不是真正的物体，而是矩阵变换的记录。视野中的物体，将做与相机相反的变换。
	GLKMatrix4 matrix = GLKMatrix4Invert(_camera.matrix, NULL);
	glLoadMatrixf((const GLfloat *)&matrix);

	// 2D和3D用的属性一般不同，所以每一次都设置一遍
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	{
		glFrontFace(GL_CW); // 将顺时针方向多边形设为正表面，符合上右下左惯例顺序
	}
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, 0); // 清空纹理
	}
}

- (void)bind2D{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat *)&_matrix2d);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// 2D和3D用的属性一般不同，所以每一次都设置一遍
	glDisable(GL_MULTISAMPLE);
//	glEnable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glEnable(GL_TEXTURE_2D);
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, 0); // 清空纹理
	}
}

- (void)draw3D{
}

- (void)draw2D{
}


- (void)addNode:(GNode *)node{
	[_nodes3d addObject:node];
}

@end
