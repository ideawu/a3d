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
	_angle = [[GEulerAngle alloc] init];
	return self;
}

- (GLKMatrix4)matrix{
	// TODO: 与欧拉角合并
	return super.matrix;
}

- (GObject *)clone{
	GObject *ret = [[GObject alloc] init];
	[ret copy:self];
	return ret;
}

- (void)copy:(GObject *)src{
	[super copy:src];
	super.matrix = src.matrix; // 注意用 super
	_angle.roll = src.angle.roll;
	_angle.pitch = src.angle.pitch;
	_angle.yaw = src.angle.yaw;
	_width = src.width;
	_height = src.height;
	_depth = src.depth;
}

- (void)scale:(float)ratio{
	_width *= ratio;
	_height *= ratio;
	_depth *= ratio;
	[super scale:ratio];
}

@end
