//  Created by ideawu on 03/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"
#import "math/GVector3.h"

// 观察者可转动视角，也可跟随一个目标
@interface GObserver : GObject

// 视角相对于自身坐标系转动的角度
@property GVector3 *angle;

// 在父坐标系中跟踪指定物体，始终保持与目标相同的相对角度和相对位置
- (void)followObject:(GObject *)target;
- (void)unfollowObject;

@end
