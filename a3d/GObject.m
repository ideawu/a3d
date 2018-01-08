//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"

@interface GObject(){
}
@end

// 在可能被继承的类，如果能用super，就不要用self.
@implementation GObject

- (id)init{
	self = [super init];
	_angle = [[GAngle alloc] init];
	return self;
}

- (GObject *)clone{
	GObject *ret = [[GObject alloc] init];
	[ret copy:self];
	return ret;
}

- (void)copy:(GObject *)src{
	[super copy:src];
	// TODO: angle, width, height...
	super.matrix = src.matrix; // 注意用 super
}

- (void)scale:(float)ratio{
	_width *= ratio;
	_height *= ratio;
	_depth *= ratio;
	[super scale:ratio];
}

@end
