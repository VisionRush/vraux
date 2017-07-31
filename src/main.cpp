#include "vraux_all.h"
#include "vraux_test.h"
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

	// Test for vraux_system
	TestForSystem();

	// Test for vraux_stringprocess
	TestForStringProcess();



#if defined Q_OS_WIN
	system("pause");
#endif

	return 0;
}




/*

time_t time_start;
time_t time_end;
double time_eps;

time_start = time(NULL);
// do something
time_end = time(NULL);
time_eps = (time_end - time_start);
printf("Use Time:%f\n", time_eps);



double dur;
clock_t c_start, c_end;

c_start = clock();
// do something

c_end = clock();
dur = (double)(c_end - c_start);
printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));



*/