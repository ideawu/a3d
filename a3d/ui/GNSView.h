//  Created by ideawu on 02/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GNSView : NSOpenGLView

// 以鼠标进入视图点为基点，当前相对基点的偏移量。
@property (readonly) NSPoint mousePoint;
@property (readonly) NSPoint mouseBasePoint;
@property (readonly) NSPoint mouseTranslate;

- (void)resetMousePoint;

@end
