//
//  AppDelegate.m
//  Scene
//
//  Created by ideawu on 15/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "AppDelegate.h"
#import "TestController.h"

@interface AppDelegate (){
	id _test;
}
@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	_test = [[TestController alloc] initWithWindowNibName:@"TestController"];
	[_test showWindow:self];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
	// Insert code here to tear down your application
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender{
	return YES;
}

- (IBAction)onNew:(id)sender {
	_test = [[TestController alloc] initWithWindowNibName:@"TestController"];
	[_test showWindow:self];
}

@end
