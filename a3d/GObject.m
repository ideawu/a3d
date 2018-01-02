//  Created by ideawu on 31/12/2017.
//  Copyright © 2017 ideawu. All rights reserved.
//

#import "GObject.h"

@interface GObject(){
}
@end

@implementation GObject

- (id)init{
	self = [super init];
	_matrix = GLKMatrix4MakeTranslation(0, 0, 0);
	return self;
}

- (const GLfloat *)glMatrix{
	return (const GLfloat *)&_matrix;
}

#pragma 物体在坐标系内的变换

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

#pragma 物体自身坐标系的变换

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

@end
