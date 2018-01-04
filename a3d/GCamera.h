//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"
#import "math/GVector3.h"

// 相机是虚拟的物体，只表示坐标系。对相机坐标系做变换，相当于对世界坐标系做相反的变换
// 相机 = 基座 + 镜头 or 相机 = 身体 + 眼睛
@interface GCamera : GObject

// 竖直方向的视角
@property float fovy;
// 镜头的转动角度(度数)
@property GVector3 *angle;

// 将自身坐标系转向视线方向
- (void)rotateToAngle;

@end
