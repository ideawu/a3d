//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"

@interface GObject(){
}
@property GObject *parent;
@end

@implementation GObject

- (id)init{
	self = [super init];
	_localMatrix = GLKMatrix4MakeTranslation(0, 0, 0);
	_angle = [[GAngle alloc] init];
	return self;
}

- (GLKMatrix4)matrix{
	GLKMatrix4 mat = _localMatrix;
	if(_parent){
		mat = GLKMatrix4Multiply(mat, GLKMatrix4Invert(_parent.matrix, NULL));
	}
	return mat;
}

#pragma mark - 物体跟随

- (void)follow:(GObject *)target{
	_parent = target;
}

- (void)unfollow{
	_localMatrix = self.matrix;
	_parent = nil;
}

#pragma mark - 物体在坐标系内的变换

- (float)x{
	return _localMatrix.m30;
}

- (float)y{
	return _localMatrix.m31;
}

- (float)z{
	return _localMatrix.m32;
}

- (void)scale:(float)ratio{
	[self scaleWidth:ratio height:ratio depth:ratio];
}

- (void)scaleWidth:(float)wRatio height:(float)hRatio depth:(float)dRatio{
	_width *= wRatio;
	_height *= hRatio;
	_depth *= dRatio;
}

#pragma mark - 物体自身坐标系的变换

- (void)moveX:(float)x y:(float)y z:(float)z{
	_localMatrix = GLKMatrix4Translate(_localMatrix, x, y, z);
}

- (void)moveX:(float)distance{
	[self moveX:distance y:0 z:0];
}

- (void)moveY:(float)distance{
	[self moveX:0 y:distance z:0];
}

- (void)moveZ:(float)distance{
	[self moveX:0 y:0 z:distance];
}

// 旋转的顺序有关系，此函数有歧义
//- (void)rotateX:(float)xDegree y:(float)yDegree z:(float)zDegree

- (void)rotateX:(float)degree{
	_localMatrix = GLKMatrix4RotateX(_localMatrix, GLKMathDegreesToRadians(degree));
}

- (void)rotateY:(float)degree{
	_localMatrix = GLKMatrix4RotateY(_localMatrix, GLKMathDegreesToRadians(degree));
}

- (void)rotateZ:(float)degree{
	_localMatrix = GLKMatrix4RotateZ(_localMatrix, GLKMathDegreesToRadians(degree));
}

- (void)rotate:(float)degree x:(float)x y:(float)y z:(float)z{
	_localMatrix = GLKMatrix4Rotate(_localMatrix, GLKMathDegreesToRadians(degree), x, y, z);
}

// 绕自身坐标系内的任意轴(p0->p1)旋转
- (void)orbit:(float)degree p0:(GLKVector3)p0 p1:(GLKVector3)p1{
	GLKVector3 vec = GLKVector3Subtract(p1, p0);
	_localMatrix = GLKMatrix4TranslateWithVector3(_localMatrix, p0);
	_localMatrix = GLKMatrix4RotateWithVector3(_localMatrix, GLKMathDegreesToRadians(degree), vec);
	_localMatrix = GLKMatrix4TranslateWithVector3(_localMatrix, GLKVector3Negate(p0));
}

- (void)orbitX:(float)degree y:(float)y z:(float)z{
	[self orbit:degree p0:GLKVector3Make(0, y, z) p1:GLKVector3Make(1, y, z)];
}

- (void)orbitY:(float)degree x:(float)x z:(float)z{
	[self orbit:degree p0:GLKVector3Make(x, 0, z) p1:GLKVector3Make(x, 1, z)];
}

- (void)orbitZ:(float)degree x:(float)x y:(float)y{
	[self orbit:degree p0:GLKVector3Make(x, y, 0) p1:GLKVector3Make(x, y, 1)];
}



@end
