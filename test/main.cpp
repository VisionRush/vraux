#include <iostream>
#include <fstream>
#include <istream>
#include <time.h>
#include "test.h"

using namespace visionrush;

int main()
{
	// Check Operate System
#if defined Q_OS_WIN
	printf("[%s:%d] libvr: os is windows.\n\n\n", __FILE__, __LINE__);
#elif defined Q_OS_LINUX
	printf("[%s:%d] libvr: os is linux.\n\n\n", __FILE__, __LINE__);
#else
#endif

	//// Test for module: vraux_filesystem
	TestForFileSystem();

	//// Test for module: vraux_system
	//TestForSystem();

	//// Test for module: vraux_stringprocess
	//TestForStringProcess();



#if defined Q_OS_WIN
	system("pause");
#endif

	return 0;
}
