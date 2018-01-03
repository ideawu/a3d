//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>
#import <GLKit/GLKit.h>
#import "math/GVector3.h"

// 新坐标系原点在父坐标系中的位置，也即父坐标系内的任意点经过变换后，在父坐标系中的位置
//		GLKVector4 zero = GLKVector4Make(0, 0, 0, 1);
//		zero = GLKMatrix4MultiplyVector4(matrix, zero);
//		NSLog(@"\n%@", [NSStringFromGLKVector4(zero) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
// 父坐标系内的任意点，在新坐标系中的位置
//		GLKVector4 pos = GLKVector4Make(x, y, z, 1);
//		pos = GLKMatrix4MultiplyVector4(GLKMatrix4Invert(matrix), pos);
//		NSLog(@"\n%@", [NSStringFromGLKVector4(zero) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
// 获取旋转角度分量
//		GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(matrix);
//		NSLog(@"quat: %@, angle: %.2f", NSStringFromGLKQuaternion(quat), GLKQuaternionAngle(quat));


// GObject=坐标系+坐标系内的物体
@interface GObject : NSObject

// 物体视角相对于自身坐标系转动的角度
@property GVector3 *angle;

@property GLKMatrix4 matrix;

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

- (GLKMatrix4)baseMatrix;
- (GLKMatrix4)angleMatrix;
// 将自身坐标系转向视线方向
- (void)rotateToAngle;

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


// 在父坐标系中跟踪指定物体，始终保持与目标相同的相对角度和相对位置
- (void)follow:(GObject *)target;
- (void)unfollow;

@end
