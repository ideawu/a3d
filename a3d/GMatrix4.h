//  Created by ideawu on 08/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <GLKit/GLKit.h>
#import "gmath.h"

@interface GMatrix4 : NSObject

@property GLKMatrix4 matrix;

// 创建一个单位矩阵
+ (GMatrix4 *)make;

- (GMatrix4 *)clone;
- (void)copy:(GMatrix4 *)src;

#pragma mark - 矩阵运算

- (void)invert;

// 将当前矩阵放入目标矩阵中，两者应在同一个世界，此操作才有意义
- (void)enter:(GMatrix4 *)target;
// 将矩阵从父矩阵中抽出，两者应是父子关系，此操作才有意义
- (void)leave:(GMatrix4 *)parent;

//- (GLKVector3)multiplyVector3:(GLKVector3)vec;
//- (GLKVector4)multiplyVector4:(GLKVector4)vec;


#pragma mark - 矩阵在父坐标系中

// 矩阵在父坐标系内的偏移
@property float x;
@property float y;
@property float z;

@property (readonly) GLKVector3 pos;

// 各轴在父坐标系内的向量
- (GLKVector3)xAxis;
- (GLKVector3)yAxis;
- (GLKVector3)zAxis;

// X轴的偏转角度
- (float)xAngle;
// Y轴的偏转角度
- (float)yAngle;
// Z轴的偏转角度
- (float)zAngle;


#pragma mark - 矩阵自身的变换

- (void)reset;
- (void)resetTranslation;
- (void)resetRotation;

- (void)scale:(float)ratio;

// 坐标原点在自身坐标方向上移动
- (void)moveX:(float)x y:(float)y z:(float)z;
- (void)moveX:(float)distance;
- (void)moveY:(float)distance;
- (void)moveZ:(float)distance;

- (void)translateX:(float)x y:(float)y z:(float)z;
- (void)translateX:(float)distance;
- (void)translateY:(float)distance;
- (void)translateZ:(float)distance;

// 坐标系绕自身的X轴旋转
- (void)rotateX:(float)degree;
// 坐标系绕自身的Y轴旋转
- (void)rotateY:(float)degree;
// 坐标系绕自身的Z轴旋转
- (void)rotateZ:(float)degree;
// 坐标系绕自身坐标内的向量(x,y,z)旋转
- (void)rotate:(float)degree x:(float)x y:(float)y z:(float)z;


#pragma mark - orbit 是一种轨道运动，将同时改变坐标系的原点位置和各轴的方向。

// 绕自身坐标系内的任意轴(p0->p1)旋转
- (void)orbit:(float)degree p0:(GLKVector3)p0 p1:(GLKVector3)p1;
// 坐标系绕与X轴平行且经过(0,y,z)线旋转
- (void)orbitX:(float)degree y:(float)y z:(float)z;
// 坐标系绕与Y轴平行且经过(0,y,z)线旋转
- (void)orbitY:(float)degree x:(float)x z:(float)z;
// 坐标系绕与Z轴平行且经过(0,y,z)线旋转
- (void)orbitZ:(float)degree x:(float)x y:(float)y;


#pragma mark - 物理力学

// 将力施加与坐标系的某一位置，当作用于标准球位置时，每一单位的力将产生一单位的位移和一单位(默认1角度)的旋转
- (void)force:(GLKVector3)force atPoint:(GLKVector3)point;
- (void)force:(GLKVector3)force atPoint:(GLKVector3)point rotationScalar:(float)radianScalar;

@end
