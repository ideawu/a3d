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
		glColor4f(0.5, 0.5, 1, 1);
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
}

@end
