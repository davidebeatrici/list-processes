#include <stdio.h>

#include <AppKit/AppKit.h>

int main()
{
	NSArray *runningApplications = [[NSWorkspace sharedWorkspace] runningApplications];
	for (NSRunningApplication *app in runningApplications) {
		printf("[%u] %s\n", [app processIdentifier], [[app bundleIdentifier] UTF8String]);
	}

	return 0;
}
