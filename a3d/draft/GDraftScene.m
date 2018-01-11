//  Created by ideawu on 03/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GDraftScene.h"

@implementation GDraftScene

- (void)draw{
	glDisable(GL_LINE_STIPPLE);

	int grids;
	int grid_width = 100;
	int depth;
	depth = self.depth;
	
	grids = self.width / grid_width;
	static GLKTextureInfo *_texture = nil;
	if(!_texture){
		NSDictionary *opts = @{GLKTextureLoaderOriginBottomLeft: @(1)};
		NSError *error = nil;
		NSString *filename = @"/Users/ideawu/Downloads/grass_top.png";
		_texture = [GLKTextureLoader textureWithContentsOfFile:filename options:opts error:&error];
		glBindTexture(GL_TEXTURE_2D, 0); // GLKTextureLoader会自动bind
	}
	glColor4f(1, 1, 1, 1); // 清除可能的tint颜色影响
	for(int i=0; i<=grids; i++){
		for(int j=0; j<=grids; j++){
			float x0 = i * grid_width;
			float z0 = j * grid_width;
			float x1 = (i+1) * grid_width;
			float z1 = (j+1) * grid_width;
			
//			glColor4f(1, 1, 1, 1);
//			glBegin(GL_POLYGON);
//			glVertex3f(x0, -5, z1);
//			glVertex3f(x1, -5, z1);
//			glVertex3f(x1, -5, z0);
//			glVertex3f(x0, -5, z0);
//			glEnd();
			
//			glBindTexture(GL_TEXTURE_2D, _texture.name);
//			glBegin(GL_POLYGON);
//			glTexCoord2f(0, 1); glVertex3f(x0, -1, z1);
//			glTexCoord2f(1, 1); glVertex3f(x1, -1, z1);
//			glTexCoord2f(1, 0); glVertex3f(x1, -1, z0);
//			glTexCoord2f(0, 0); glVertex3f(x0, -1, z0);
//			glEnd();
//			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}


	// 地板
	grids = self.width / grid_width;
//	log_debug(@"%d %d %f %f", grids, grid_width, self.width, self.depth);
	for(int i=0; i<=grids; i++){
		if(i == 0){
			glLineWidth(1);
		}else{
			glLineWidth(0.5);
		}
		float v = grid_width * i;
		glColor4f(0.9, 0.9, 1, 1);
		glBegin(GL_LINES);
		{
			// x
			glVertex3f(0, 0, v);
			glVertex3f(depth, 0, v);
			// z
			glVertex3f(v, 0, 0);
			glVertex3f(v, 0, depth);
		}
		glEnd();
	}

	// 左边墙
	grids = self.height / grid_width;
	for(int i=0; i<=grids; i++){
		if(i == 0){
			glLineWidth(1);
		}else{
			glLineWidth(0.5);
		}
		float v = grid_width * i;
		glColor4f(1, 1, 0.5, 1);
		glBegin(GL_LINES);
		{
			// y
			glVertex3f(0, 0, v);
			glVertex3f(0, depth, v);
			// z
			glVertex3f(0, v, 0);
			glVertex3f(0, v, depth);
		}
		glEnd();
	}
	
	// 画一条额外的z轴
	glLineWidth(2);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_LINES);
	{
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, depth);
	}
	glEnd();
	
	
	[self test];
}

- (void)test{
}

@end
