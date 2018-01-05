//  Created by ideawu on 04/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GDraftSprite.h"

@interface GDraftSprite(){
}
@end

@implementation GDraftSprite

- (id)init{
	self = [super init];
	_color = GLKVector4Make(0.8, 0.8, 0.8, 1);
	return self;
}

- (GLKMatrix4)matrix{
	GLKMatrix4 mat = super.matrix;
	mat = GLKMatrix4Multiply(mat, self.angle.matrix);
	return mat;
}

// 以视线坐标为基准来移动
- (void)moveX:(float)x y:(float)y z:(float)z{
	GLKMatrix4 mat1 = self.matrix;
	GLKMatrix4 mat2 = GLKMatrix4Translate(mat1, x, y, z);
	GLKMatrix4 mat3 = GLKMatrix4Subtract(mat2, mat1);
	super.matrix = GLKMatrix4Add(super.matrix, mat3);
}

// 相机绕Y轴的旋转比较特殊，始终保持相机基座与父坐标系Y轴的角度
- (void)rotateY:(float)degree{
	// p * -p * n * t * -n * p
	GLKMatrix4 mat = GLKMatrix4MakeTranslation(self.x, self.y, self.z); // Y轴坐标系
	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
	mat = GLKMatrix4Translate(mat, -self.x, -self.y, -self.z); // 退出Y轴坐标系
	mat = GLKMatrix4Multiply(mat, super.matrix);
	super.matrix = mat;
}

- (void)draw{
	[self drawHead];

	glPushMatrix();
	GLKMatrix4 mat = GLKMatrix4Invert(self.angle.matrix, NULL);
	glMultMatrixf((const GLfloat *)&mat);
	[self drawBody];
	glPopMatrix();
}

- (void)drawHead{
//	float x0 = 0 - self.width/2;
//	float y0 = 0 - self.height/2;
	float z0 = 0 - self.depth/2;
//	float x1 = 0 + self.width/2;
	float y1 = 0 + self.height/2;
	float z1 = 0 + self.depth/2;
	
	// 方向-线
	glLineWidth(3);
	glColor4f(1, 1, 0, 1);
	glBegin(GL_LINES);
	{
		glVertex3f(0, y1, z0);
		glVertex3f(0, y1, z1-20);
	}
	glEnd();
	// 方向-箭头
	glDisable(GL_CULL_FACE);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_POLYGON);
	{
		glVertex3f(0, y1, z1);
		glVertex3f(-10, y1, z1-20);
		glVertex3f(10, y1, z1-20);
	}
	glEnd();
	glEnable(GL_CULL_FACE);
}

- (void)drawBody{
	float x0 = 0 - self.width/2;
	float y0 = 0 - self.height/2;
	float z0 = 0 - self.depth/2;
	float x1 = 0 + self.width/2;
	float y1 = 0 + self.height/2;
	float z1 = 0 + self.depth/2;
	
	// 底面
	glDisable(GL_CULL_FACE);
	glColor4f(_color.r, _color.g, _color.b, _color.a);
	glBegin(GL_POLYGON);
	{
		glVertex3f(x0, y0, z0);
		glVertex3f(x1, y0, z0);
		glVertex3f(x1, y0, z1);
		glVertex3f(x0, y0, z1);
//		log_debug(@"%f %f", z0, z1);
	}
	glEnd();
	glEnable(GL_CULL_FACE);
	
	// Y轴线
	glLineWidth(1);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_LINES);
	{
		glVertex3f(0, y0, 0);
		glVertex3f(0, y1, 0);
	}
	glEnd();

	// 方向-线
	glLineWidth(2);
	glColor4f(0, 0, 1, 1);
	glBegin(GL_LINES);
	{
		glVertex3f(0, -20, z0);
		glVertex3f(0, -20, z1-20);
	}
	glEnd();
	// 方向-箭头
	glDisable(GL_CULL_FACE);
	glColor4f(1, 0.5, 0.5, 1);
	glBegin(GL_POLYGON);
	{
		glVertex3f(0, -20, z1);
		glVertex3f(-10, -20, z1-20);
		glVertex3f(10, -20, z1-20);
	}
	glEnd();
	glEnable(GL_CULL_FACE);

}

@end
