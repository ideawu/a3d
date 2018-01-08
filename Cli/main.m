
#import <Foundation/Foundation.h>
#import "GMatrix4.h"

int main(int argc, const char * argv[]) {
	GMatrix4 *mat = [GMatrix4 make];
	log_debug(@"\n%@", mat);
	[mat moveX:10 y:10 z:10];
	log_debug(@"\n%@", mat);
	[mat rotateZ:45];
	log_debug(@"\n%@", mat);
	[mat moveX:1 y:0 z:0];
	log_debug(@"\n%@", mat);
	[mat resetRotation];
	log_debug(@"\n%@", mat);
	return 0;
}
