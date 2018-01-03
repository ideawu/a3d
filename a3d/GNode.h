//  Created by ideawu on 28/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "GObject.h"

/*
 物体的 Z 轴为前后，Y 轴为上下，X轴为左右。
 操作物体的移动，旋转等，均在自身坐标中进行，完成后，更新其中点的世界坐标和方向(axis)。
 */

@interface GNode : GObject

// 子类一般不重写此方法，而应该重写 draw 方法。
- (void)render;

// 子类应该重写此方法，进行三维世界的渲染
- (void)draw;

@end
