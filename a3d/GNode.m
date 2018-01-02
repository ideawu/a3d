//  Created by ideawu on 28/12/2017.
//  Copyright © 2017 ideawu. All rights reserved.
//

#import "GNode.h"

@interface GNode()
@end

@implementation GNode

- (void)render{
	glPushMatrix();
	glMultMatrixf(self.glMatrix);
	[self draw];
	glPopMatrix();
}

- (void)draw{
}

@end
