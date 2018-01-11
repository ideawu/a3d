//  Created by ideawu on 11/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GFollow.h"

@interface GFollow(){
	GMatrix4 *_target;
}
@end


@implementation GFollow

- (id)init{
	self = [super init];
	_origin = [[GMatrix4 alloc] init];
	return self;
}

+ (GFollow *)followTarget:(GMatrix4 *)target{
	GFollow *ret = [[GFollow alloc] init];
	[ret setTarget:target];
	return ret;
}

- (GMatrix4 *)target{
	return _target;
}

- (void)setTarget:(GMatrix4 *)target{
	_origin.matrix = target.matrix;
	_target = target;
}

@end
