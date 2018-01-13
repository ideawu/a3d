//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"
#import "GFollow.h"
#import "GRay.h"

// 相机是虚拟的物体，只表示坐标系。对相机坐标系做变换，相当于对世界坐标系做相反的变换
// 相机 = 基座 + 镜头 or 相机 = 身体 + 眼睛
// 相机的世界坐标将考虑视线角度。
@interface GCamera : GObject

@property (readonly) GLKMatrix4 matrix3d;
@property (readonly) GLKMatrix4 matrix2d;

// 竖直方向的视角
@property float fovy;

@property GFollow *follow;

- (void)setup;
- (void)bind3D;
- (void)bind2D;


- (GRay *)rayFromScreenPointX:(float)x y:(float)y;


// 在父坐标系中跟踪指定物体，始终保持与目标相同的相对角度和相对位置
- (void)follow:(GObject *)target;
- (void)unfollow;

@end
