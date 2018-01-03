//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"

@interface GObject(){
	GLKMatrix4 _matrix;
}
@property GObject *target;
@property GLKMatrix4 targetOldMatrix;
@end

@implementation GObject

- (id)init{
	self = [super init];
	_angle = [[GVector3 alloc] init];
	_matrix = GLKMatrix4MakeTranslation(0, 0, 0);
	return self;
}

- (GLKMatrix4)angleMatrix{
	GLKMatrix4 mat = _matrix;
	mat = GLKMatrix4RotateX(mat, GLKMathDegreesToRadians(_angle.x));
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(_angle.y));
	mat = GLKMatrix4RotateZ(mat, GLKMathDegreesToRadians(_angle.z));
	return mat;
}

// self.matrix = _matrix * angle * _follow
- (GLKMatrix4)matrix{
//	log_debug(@"%f %f %f", _angle.x, _angle.y, _angle.z);
	GLKMatrix4 mat = [self angleMatrix];
	if(_target){
		// p * -p * old * diff * p * -old
		// = new * p * -old
		mat = GLKMatrix4Multiply(_target.matrix, mat);
		mat = GLKMatrix4Multiply(mat, GLKMatrix4Invert(_targetOldMatrix, NULL));
	}
	return mat;
}

- (void)setMatrix:(GLKMatrix4)matrix{
	_matrix = matrix;
}

#pragma mark - 物体在坐标系内的变换

- (float)x{
	return _matrix.m30;
}

- (float)y{
	return _matrix.m31;
}

- (float)z{
	return _matrix.m32;
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

- (void)rotateToAngle{
	_matrix = [self angleMatrix];
	[_angle reset];
}

- (void)moveX:(float)x y:(float)y z:(float)z{
	_matrix = GLKMatrix4Translate(_matrix, x, y, z);
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
	_matrix = GLKMatrix4RotateX(_matrix, GLKMathDegreesToRadians(degree));
}

- (void)rotateY:(float)degree{
	_matrix = GLKMatrix4RotateY(_matrix, GLKMathDegreesToRadians(degree));
}

- (void)rotateZ:(float)degree{
	_matrix = GLKMatrix4RotateZ(_matrix, GLKMathDegreesToRadians(degree));
}

- (void)rotate:(float)degree x:(float)x y:(float)y z:(float)z{
	_matrix = GLKMatrix4Rotate(_matrix, GLKMathDegreesToRadians(degree), x, y, z);
}

// 绕自身坐标系内的任意轴(p0->p1)旋转
- (void)orbit:(float)degree p0:(GLKVector3)p0 p1:(GLKVector3)p1{
	GLKVector3 vec = GLKVector3Subtract(p1, p0);
	_matrix = GLKMatrix4TranslateWithVector3(_matrix, p0);
	_matrix = GLKMatrix4RotateWithVector3(_matrix, GLKMathDegreesToRadians(degree), vec);
	_matrix = GLKMatrix4TranslateWithVector3(_matrix, GLKVector3Negate(p0));
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


#pragma mark - 物体跟随

- (void)follow:(GObject *)target{
	_target = target;
	_targetOldMatrix = target.matrix;
}

- (void)unfollow{
	// p * -p * old * diff * p * -old
	// = new * p * -old
	_matrix = GLKMatrix4Multiply(_target.matrix, _matrix);
	_matrix = GLKMatrix4Multiply(_matrix, GLKMatrix4Invert(_targetOldMatrix, NULL));
	_target = nil;
}


@end
