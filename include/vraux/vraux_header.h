// 3rdparty header
#include "vraux/vrglobalcheck.h"
// c++ header
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime> 
#include <chrono>
#include <istream>
#include <fstream>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>  
// system header
#if defined Q_OS_WIN
#include <io.h>
#include <direct.h>
#include <Windows.h>
#include <TlHelp32.h> 
#elif defined Q_OS_LINUX
#include <sys/stat.h>  
#include <unistd.h> 
#include <dirent.h>
#include <signal.h>
#else

#endif

// macro definition
#if defined Q_OS_WIN
	#define VR_API __declspec(dllexport)
#else
	#define VR_API
#endif

using namespace std;