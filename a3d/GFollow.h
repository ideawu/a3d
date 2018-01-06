//  Created by ideawu on 06/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"

@interface GFollow : NSObject

@property GObject *target;

- (void)followTranslate;
- (void)followRotate;
- (void)followRotateX;
- (void)followRotateY;
- (void)followRotateZ;

// 获取目标从开始跟踪到当前所经过的变换
- (GLKMatrix4)matrix;

@end
