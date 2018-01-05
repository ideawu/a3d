//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <GLKit/GLKit.h>
#import "GAngle.h"

// 新坐标系原点在父坐标系中的位置，也即父坐标系内的任意点经过变换后，在父坐标系中的位置
//		GLKVector4 zero = GLKVector4Make(0, 0, 0, 1);
//		zero = GLKMatrix4MultiplyVector4(matrix, zero);
// 父坐标系内的任意点，在新坐标系中的位置
//		pos = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(matrix), pos);
// 获取旋转角度分量
//		GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(matrix);
// 将同一世界内的某坐标系移到另一坐标系内，可用于物体跟随
//		GLKMatrix4Multiply(A, GLKMatrix4Invert(B));
// 将某坐标系A从另一坐标系B当中移出
//		GLKMatrix4Multiply(B, A);


// GObject=坐标系+坐标系内的物体
@interface GObject : NSObject

// 物体在世界中的坐标系
@property GLKMatrix4 matrix;

@property GAngle *angle;

// 物体在父坐标系中的坐标(不随follow即时更新，unfollow后才更新)
@property (readonly) float x;
@property (readonly) float y;
@property (readonly) float z;

// 物体在父坐标系中的体积
@property float width;
@property float height;
@property float depth;

// scale只改变体积，不改变坐标系！
- (void)scale:(float)ratio;
- (void)scaleWidth:(float)wRatio height:(float)hRatio depth:(float)dRatio;
// zoom: 改变坐标系，不改变物体


// 坐标原点在自身坐标方向上移动
- (void)moveX:(float)xDistance y:(float)yDistance z:(float)zDistance;
- (void)moveX:(float)distance;
- (void)moveY:(float)distance;
- (void)moveZ:(float)distance;

// 坐标系绕自身的X轴旋转
- (void)rotateX:(float)degree;
// 坐标系绕自身的Y轴旋转
- (void)rotateY:(float)degree;
// 坐标系绕自身的Z轴旋转
- (void)rotateZ:(float)degree;
// 坐标系绕自身坐标内的向量(x,y,z)旋转
- (void)rotate:(float)degree x:(float)x y:(float)y z:(float)z;


// orbit 是一种轨道运动，将同时改变坐标系的原点位置和各轴的方向。

// 坐标系绕与X轴平行且经过(0,y,z)线旋转
- (void)orbitX:(float)degree y:(float)y z:(float)z;
// 坐标系绕与Y轴平行且经过(0,y,z)线旋转
- (void)orbitY:(float)degree x:(float)x z:(float)z;
// 坐标系绕与Z轴平行且经过(0,y,z)线旋转
- (void)orbitZ:(float)degree x:(float)x y:(float)y;

@end
