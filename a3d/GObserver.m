//  Created by ideawu on 03/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObserver.h"

@interface GObserver(){
}
@property GObject *target;
@property GLKMatrix4 targetOldMatrix;
@end


@implementation GObserver

- (id)init{
	self = [super init];
	_angle = [[GVector3 alloc] init];
	return self;
}

// GObject 的 matrix 方法被重写
- (GLKMatrix4)matrix{
	GLKMatrix4 mat = super.matrix; // 注意是 super
	mat = GLKMatrix4RotateX(mat, GLKMathDegreesToRadians(_angle.x));
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(_angle.y));
	mat = GLKMatrix4RotateZ(mat, GLKMathDegreesToRadians(_angle.z));
	if(_target){
		// p * -p * old * diff * p * -old
		// = new * p * -old
		mat = GLKMatrix4Multiply(_target.matrix, mat);
		mat = GLKMatrix4Multiply(mat, GLKMatrix4Invert(_targetOldMatrix, NULL));
	}
	return mat;
}

#pragma mark - 目标跟随

- (void)followObject:(GObject *)target{
	_target = target;
	_targetOldMatrix = target.matrix;
}

- (void)unfollowObject{
	// 将真正的坐标系更新，并清除视角和跟随目标
	super.matrix = self.matrix;
	_angle.x = 0;
	_angle.y = 0;
	_angle.z = 0;
	_target = nil;
}

@end
