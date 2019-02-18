//  Created by ideawu on 02/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "AppDelegate.h"
#import "TestController.h"
#import "AnimationWindow.h"
#import "TransparencyWindow.h"

@interface AppDelegate (){
	TestController *_test;
	AnimationWindow *_animationWindow;
	TransparencyWindow *_transparencyWindow;
}
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
//	_test = [[TestController alloc] initWithWindowNibName:@"TestController"];
//	_test.appDelegate = self;
//	[_test showWindow:self];
//
//	_animationWindow = [[AnimationWindow alloc] initWithWindowNibName:@"AnimationWindow"];
//	[_animationWindow showWindow:self];
	
	_transparencyWindow = [[TransparencyWindow alloc] initWithWindowNibName:@"TransparencyWindow"];
	[_transparencyWindow showWindow:self];
}

- (void)windowWillClose:(NSWindowController *)controller{
//	log_debug(@"%s", __func__);
	if(controller == _test){
		_test = nil;
	}
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
	// Insert code here to tear down your application
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender{
	return YES;
}

- (IBAction)onNewAction:(id)sender {
	log_debug(@"");
}

@end
