//  Created by ideawu on 31/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>
#import <GLKit/GLKit.h>

// 在父坐标中的位置
//		GLKVector4 zero = GLKVector4Make(0, 0, 0, 1);
//		zero = GLKMatrix4MultiplyVector4(_world.camera.matrix, zero);
//		NSLog(@"\n%@", [NSStringFromGLKVector4(zero) stringByReplacingOccurrencesOfString:@"}, " withString:@"},\n"]);
// 获取旋转角度
//		GLKQuaternion quat = GLKQuaternionMakeWithMatrix4(_world.camera.matrix);
//		NSLog(@"quat: %@, angle: %.2f", NSStringFromGLKQuaternion(quat), GLKQuaternionAngle(quat));


@interface GObject : NSObject

@property GLKMatrix4 matrix;

// 物体在自身坐标系中的坐标
@property (readonly) float x;
@property (readonly) float y;
@property (readonly) float z;

// 物体在父坐标系中的体积
@property float width;
@property float height;
@property float depth;

- (const GLfloat *)glMatrix;

// scale只改变体积，不改变坐标系！
- (void)scale:(float)ratio;
- (void)scaleWidth:(float)wRatio height:(float)hRatio depth:(float)dRatio;


// 物体在自身坐标上移动
- (void)moveX:(float)xDistance y:(float)yDistance z:(float)zDistance;
- (void)moveX:(float)distance;
- (void)moveY:(float)distance;
- (void)moveZ:(float)distance;

// 物体绕自身的X轴旋转
- (void)rotateX:(float)degree;
// 物体绕自身的Y轴旋转
- (void)rotateY:(float)degree;
// 物体绕自身的Z轴旋转
- (void)rotateZ:(float)degree;
// 物体绕自身坐标内的向量(x,y,z)旋转
- (void)rotate:(float)degree x:(float)x y:(float)y z:(float)z;

@end
