//
//  DraftImage.cpp
//  a3d
//
//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "DraftImage.h"
#import <GLKit/GLKit.h>

// 如果不在构造函数初始列表里置空objc对象，编译器会调用[objc release]导致出错
DraftImage::DraftImage():_texture(nil){
}

DraftImage::~DraftImage(){
	if(_texture){
		_texture = nil;
	}
}

DraftImage::DraftImage(const char *filename){
	NSString *fn = [[NSString alloc] initWithUTF8String:filename];
	NSDictionary *opts = @{GLKTextureLoaderOriginBottomLeft: @(1)};
	NSError *error = nil;
	_texture = [GLKTextureLoader textureWithContentsOfFile:fn options:opts error:&error];
	if(error){
		log_debug(@"%@", error);
	}
	glBindTexture(GL_TEXTURE_2D, 0); // GLKTextureLoader会自动bind
	//	log_debug(@"%@", _texture);
	this->width([(GLKTextureInfo *)_texture width]);
	this->height([(GLKTextureInfo *)_texture height]);
}

void DraftImage::scale(float xyz){
	this->scale(xyz, xyz, xyz);
}

void DraftImage::scale(float x, float y, float z){
	// 不缩放坐标系
	//	((a3d::Matrix4 *)this)->scale(x, y, z);
	this->width(this->width() * x);
	this->height(this->height() * y);
	this->depth(this->depth() * z);
}

void DraftImage::draw(){
	float x0 = 0 - this->width()/2;
	float y0 = 0 - this->height()/2;
	float x1 = 0 + this->width()/2;
	float y1 = 0 + this->height()/2;
	float z = 0;
	//	log_debug(@"%.2f %.2f %.2f %.2f", x0, y0, x1, y1);
	
	// 注意，正反面均贴图，或者禁用 GL_CULL_FACE 后贴图，两种方式的优劣？
	//	glDisable(GL_CULL_FACE);
	// TODO: 此选项能否启用图片的 alpha 通道？
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glColor4f(1, 1, 1, 1); // 清除可能的tint颜色影响
	glBindTexture(GL_TEXTURE_2D, [(GLKTextureInfo *)_texture name]);
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0, 1); glVertex3f(x0, y1, z);
		glTexCoord2f(1, 1); glVertex3f(x1, y1, z);
		glTexCoord2f(1, 0); glVertex3f(x1, y0, z);
		glTexCoord2f(0, 0); glVertex3f(x0, y0, z);
	}
	glEnd();
	glBegin(GL_POLYGON);
	{
		glTexCoord2f(0, 1); glVertex3f(x1, y1, z);
		glTexCoord2f(1, 1); glVertex3f(x0, y1, z);
		glTexCoord2f(1, 0); glVertex3f(x0, y0, z);
		glTexCoord2f(0, 0); glVertex3f(x1, y0, z);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

