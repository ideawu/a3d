//  Created by ideawu on 28/12/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>
#import <GLKit/GLKit.h>

@interface GFrame : NSObject

@property int width;
@property int height;

- (id)initWithWidth:(int)width height:(int)height;

- (void)bind;
- (void)flush;

@end
