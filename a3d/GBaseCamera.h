//  Created by ideawu on 06/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"

@interface GBaseCamera : GObject

// 竖直方向的视角
@property float fovy;
// 观察的焦点在相机坐标系内的位置，默认为相机原点
@property GLKVector3 center;

@end
