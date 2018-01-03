//  Created by ideawu on 28/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GNode.h"

@interface GNode()
@end

@implementation GNode

- (void)render{
	glPushMatrix();
	GLKMatrix4 mat = self.matrix;
	glMultMatrixf((const GLfloat *)&mat);
	[self draw];
	glPopMatrix();
}

- (void)draw{
}

@end
