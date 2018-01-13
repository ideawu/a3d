//  Created by ideawu on 04/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "DraftSprite.h"
#import <GLKit/GLKit.h>

DraftSprite::DraftSprite(){
	color = a3d::Color::grey();
}

void DraftSprite::draw(){
	drawHead();

//	glPushMatrix();
//	GLKMatrix4 mat = GLKMatrix4Invert(self.angle.matrix, NULL);
//	glMultMatrixf((const GLfloat *)&mat);
	
	drawBody();
	
//	glPopMatrix();
}

void DraftSprite::drawHead(){
//	float x0 = 0 - this->width()/2;
//	float y0 = 0 - this->height()/2;
	float z0 = 0 - this->depth()/2;
//	float x1 = 0 + this->width()/2;
	float y1 = 0 + this->height()/2;
	float z1 = 0 + this->depth()/2;
	
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

void DraftSprite::drawBody(){
	float x0 = 0 - this->width()/2;
	float y0 = 0 - this->height()/2;
	float z0 = 0 - this->depth()/2;
	float x1 = 0 + this->width()/2;
	float y1 = 0 + this->height()/2;
	float z1 = 0 + this->depth()/2;
	
	// 底面
	glDisable(GL_CULL_FACE);
	glColor4f(color.r, color.g, color.b, color.a);
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

