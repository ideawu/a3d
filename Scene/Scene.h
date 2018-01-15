//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <SceneKit/SceneKit.h>

@interface Scene : NSObject

@property (readonly) SCNCamera *camera;
@property CFTimeInterval sceneTime;

- (id)initWithViewportWidth:(float)width height:(float)height depth:(float)depth;

- (void)addNode:(SCNNode *)node;
- (void)render;

@end
