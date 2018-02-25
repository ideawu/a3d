//  Created by ideawu on 02/01/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#import "AppDelegate.h"
#import "TestController.h"

@interface AppDelegate (){
	TestController *_test;
	TestController *_test2;
}
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
//	_test2 = [[TestController alloc] initWithWindowNibName:@"TestController"];
//	_test2.appDelegate = self;
//	[_test2 showWindow:self];

	_test = [[TestController alloc] initWithWindowNibName:@"TestController"];
	_test.appDelegate = self;
	[_test showWindow:self];
}

- (void)windowWillClose:(NSWindowController *)controller{
//	log_debug(@"%s", __func__);
	if(controller == _test){
		_test = nil;
	}
	if(controller == _test2){
		_test2 = nil;
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
