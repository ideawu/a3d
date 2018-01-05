//
//  MySprite.m
//  Test
//
//  Created by ideawu on 05/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "MySprite.h"

@implementation MySprite

- (void)draw{
	static GLKTextureInfo *_texture = nil;
	if(!_texture){
		NSDictionary *opts = @{GLKTextureLoaderOriginBottomLeft: @(0)};
		NSError *error = nil;
		NSString *filename = @"/Users/ideawu/Downloads/alex.png";
		_texture = [GLKTextureLoader textureWithContentsOfFile:filename options:opts error:&error];
	}

	float scale = 20;
	glScalef(scale, scale, scale);

	glBindTexture(GL_TEXTURE_2D, _texture.name);
	glColor4f(1, 1, 1, 1); // 清除可能的tint颜色影响
#include "test.c"
	glBindTexture(GL_TEXTURE_2D, 0);
}

@end
