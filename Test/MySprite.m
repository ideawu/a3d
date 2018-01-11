//
//  MySprite.m
//  Test
//
//  Created by ideawu on 05/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "MySprite.h"

@implementation MySprite

- (GLKMatrix4)matrix{
	GLKMatrix4 mat = super.matrix;
//	mat = GLKMatrix4Multiply(mat, self.angle.matrix);
	return mat;
}

// 相机绕Y轴的旋转比较特殊，始终保持相机基座与父坐标系Y轴的角度
//- (void)rotateY:(float)degree{
//	// p * -p * n * t * -n * p
//	GLKMatrix4 mat = GLKMatrix4MakeTranslation(self.x, self.y, self.z); // Y轴坐标系
//	mat = GLKMatrix4RotateY(mat, GLKMathDegreesToRadians(degree));
//	mat = GLKMatrix4Translate(mat, -self.x, -self.y, -self.z); // 退出Y轴坐标系
//	mat = GLKMatrix4Multiply(mat, super.matrix);
//	super.matrix = mat;
//}

- (void)draw{
	static GLKTextureInfo *_texture = nil;
	if(!_texture){
		NSDictionary *opts = @{GLKTextureLoaderOriginBottomLeft: @(0)};
		NSError *error = nil;
		NSString *filename = @"/Users/ideawu/Downloads/alex.png";
		_texture = [GLKTextureLoader textureWithContentsOfFile:filename options:opts error:&error];
		glBindTexture(GL_TEXTURE_2D, 0); // GLKTextureLoader会自动bind
	}
	
	glBindTexture(GL_TEXTURE_2D, _texture.name);
	glColor4f(1, 1, 1, 1); // 清除可能的tint颜色影响

	float scale = 10;
	glScalef(scale, scale, scale);

	[self drawHead];
	
	glPushMatrix();
	GLKMatrix4 mat = GLKMatrix4Invert(self.angle.matrix, NULL);
	glMultMatrixf((const GLfloat *)&mat);
	[self drawBody];
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

- (void)drawHead{
	// head
	glPushMatrix();
	glTranslatef(0, 8, 0);
	glTranslatef(0, 24, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.125, 0); glVertex3f(-3.5, 5, 4.5);
	glTexCoord2f(0.25, 0); glVertex3f(4.5, 5, 4.5);
	glTexCoord2f(0.25, 0.125); glVertex3f(4.5, 5, -3.5);
	glTexCoord2f(0.125, 0.125); glVertex3f(-3.5, 5, -3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0); glVertex3f(4.5, -3, 4.5);
	glTexCoord2f(0.375, 0); glVertex3f(-3.5, -3, 4.5);
	glTexCoord2f(0.375, 0.125); glVertex3f(-3.5, -3, -3.5);
	glTexCoord2f(0.25, 0.125); glVertex3f(4.5, -3, -3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.125); glVertex3f(-3.5, 5, 4.5);
	glTexCoord2f(0.125, 0.125); glVertex3f(-3.5, 5, -3.5);
	glTexCoord2f(0.125, 0.25); glVertex3f(-3.5, -3, -3.5);
	glTexCoord2f(0, 0.25); glVertex3f(-3.5, -3, 4.5);
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.125, 0.125); glVertex3f(-3.5, 5, -3.5);
	glTexCoord2f(0.25, 0.125); glVertex3f(4.5, 5, -3.5);
	glTexCoord2f(0.25, 0.25); glVertex3f(4.5, -3, -3.5);
	glTexCoord2f(0.125, 0.25); glVertex3f(-3.5, -3, -3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0.125); glVertex3f(4.5, 5, -3.5);
	glTexCoord2f(0.375, 0.125); glVertex3f(4.5, 5, 4.5);
	glTexCoord2f(0.375, 0.25); glVertex3f(4.5, -3, 4.5);
	glTexCoord2f(0.25, 0.25); glVertex3f(4.5, -3, -3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.375, 0.125); glVertex3f(4.5, 5, 4.5);
	glTexCoord2f(0.5, 0.125); glVertex3f(-3.5, 5, 4.5);
	glTexCoord2f(0.5, 0.25); glVertex3f(-3.5, -3, 4.5);
	glTexCoord2f(0.375, 0.25); glVertex3f(4.5, -3, 4.5);
	glEnd();
	
	glPopMatrix();
}

- (void)drawBody{
#include "test.c"
}

@end
