//  Created by ideawu on 04/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <GLKit/GLKit.h>

// EulerAngle 用于表示视线方向等。
@interface GAngle : NSObject

// 视线相对于父坐标各轴转运的角度(度数)
@property float x;
@property float y;
@property float z;

- (GLKMatrix4)matrix;

- (void)reset;

@end
