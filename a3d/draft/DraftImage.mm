//
//  DraftImage.cpp
//  a3d
//
//  Created by ideawu on 13/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "DraftImage.h"
#import <GLKit/GLKit.h>

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
	this->width(_texture.width);
	this->height(_texture.height);
}

void DraftScene::draw(){
}

