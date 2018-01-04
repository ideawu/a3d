//  Created by ideawu on 04/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GAngle.h"

@implementation GAngle

- (void)reset{
	_x = _y = _z = 0;
}

// 眼睛坐标系是相对于基座坐标系的
- (GLKMatrix4)matrix{
	// 注意顺序，我们要求如果不旋转z轴时，x轴应该保持在x-z平面上，所以先旋转y轴再旋转x轴。
	GLKMatrix4 mat = GLKMatrix4MakeTranslation(0, 0, 0);
	mat = GLKMatrix4RotateZ(mat, GLKMathDegreesToRadians(_z));
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(_y));
	mat = GLKMatrix4RotateX(mat, GLKMathDegreesToRadians(_x));
	return mat;
}

@end
