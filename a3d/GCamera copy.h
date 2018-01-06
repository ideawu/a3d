//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"

// 相机是虚拟的物体，只表示坐标系。对相机坐标系做变换，相当于对世界坐标系做相反的变换
// 相机 = 基座 + 镜头 or 相机 = 身体 + 眼睛
// 相机的世界坐标将考虑视线角度。
@interface GCamera : GObject

// 竖直方向的视角
@property float fovy;

@property (readonly) GObject *target;

// 相机身体在世界（不是在被跟随物体中）坐标中的坐标系
//- (GLKMatrix4)bodyMatrix;

// 按相机特有的操作顺序，先后旋转 z-y-z 轴
- (void)rotateX:(float)x y:(float)y z:(float)z;

// 在父坐标系中跟踪指定物体，始终保持与目标相同的相对角度和相对位置
- (void)follow:(GObject *)target;
- (void)unfollow;

@end
