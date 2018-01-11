//  Created by ideawu on 11/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"

@interface GFollow : NSObject

@property (readonly) GMatrix4 *origin;
@property (retain, readonly) GMatrix4 *target;

+ (GFollow *)followTarget:(GMatrix4 *)target;

- (void)setTarget:(GMatrix4 *)target;

@end
