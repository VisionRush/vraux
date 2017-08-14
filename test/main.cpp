#include "test.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <time.h>

using namespace visionrush;

int main()
{
#if defined Q_OS_WIN
	printf("libvr: os is windows.\n\n\n");
#elif defined Q_OS_LINUX
	printf("libvr: os is linux.\n\n\n");
#else
#endif

	// Test for vraux_filesystem
	TestForFileSystem();

	//// Test for vraux_system
	//TestForSystem();

	//// Test for vraux_stringprocess
	//TestForStringProcess();



#if defined Q_OS_WIN
	system("pause");
#endif

	return 0;
}
