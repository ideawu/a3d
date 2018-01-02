//  Created by ideawu on 28/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GImage.h"
#import <GLKit/GLKit.h>

@interface GImage (){
}
@property GLKTextureInfo *texture;
@end

@implementation GImage

- (id)initWithContentsOfFile:(NSString *)filename{
	self = [super init];
	NSDictionary *opts = @{GLKTextureLoaderOriginBottomLeft: @(1)};
	NSError *error = nil;
	_texture = [GLKTextureLoader textureWithContentsOfFile:filename options:opts error:&error];
	if(error){
		log_debug(@"%@", error);
	}
//	log_debug(@"%@", _texture);
	self.width = _texture.width;
	self.height = _texture.height;
	return self;
}

- (void)draw{
	float x0 = 0 - self.width/2;
	float y0 = 0 - self.height/2;
	float x1 = 0 + self.width/2;
	float y1 = 0 + self.height/2;
	float z = 0;
//	log_debug(@"%.2f %.2f %.2f %.2f", x0, y0, x1, y1);

	// 注意，正反面均贴图，或者禁用 GL_CULL_FACE 后贴图，两种方式的优劣？
//	glDisable(GL_CULL_FACE);
	// TODO: 此选项能否启用图片的 alpha 通道？
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 清除可能的tint颜色影响
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, _texture.name);
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

@end
