#include "test.h"

void TestForStringProcess()
{
	printf("***************************************************\n");
	printf("*                                                 *\n");
	printf("*          Module: vraux_stringprocess            *\n");
	printf("*                                                 *\n");
	printf("***************************************************\n\n");

	VRStringProcTool vrtool;

	// -----------------------------------------------
	// Test for Split
	// -----------------------------------------------
	{
		printf("libvr: Split.\n");
		printf("------------------------------------------\n");
		string str;
		vector<string> vec_item;
		// 1
		str = "Hello I am comming!";
		vrtool.Split(str, ' ', vec_item);
		printf("libvr: %s, delimiter is ' '\n", str.c_str());
		for (size_t i = 0; i < vec_item.size(); i++)
			printf("%s\n", vec_item[i].c_str());
		printf("\n\n");

		// 2
		vec_item.clear();
		str = "Hello--I--am--comming!";
		vrtool.Split(str, "--", vec_item);
		printf("libvr: %s, delimiter is \"--\"\n", str.c_str());
		for (size_t i = 0; i < vec_item.size(); i++)
			printf("%s\n", vec_item[i].c_str());
		printf("\n\n");
	}
	

	// -----------------------------------------------
	// Test for Replace
	// -----------------------------------------------
	{
		printf("libvr: Replace.\n");
		printf("------------------------------------------\n");
		string intput_str;
		string output_str;

		intput_str = "Hello, I am comming!";
		printf("libvr: ori: %s.\n", intput_str.c_str());
		vrtool.Replace(intput_str, output_str, ",", " world,");
		printf("libvr: dst: %s.\n", output_str.c_str());
		printf("\n\n");
	}

	// ---------------------------
	// Test for Character set conversion
	// ---------------------------
	{
		printf("libvr: UTF8ToGB (test in windows 10).\n");
		printf("------------------------------------------\n");
		string path = "videopath.txt";
		vector<string> filePaths;
		ifstream ifs(path);
		if (!ifs.is_open())
			return;
		string line;
		while (getline(ifs, line))
		{
			filePaths.push_back(line);
			printf("libvr: ori: %s \n", line.c_str());
			vrtool.UTF8ToGB(line, line);
			printf("libvr: dst: %s \n", line.c_str());
		}
		ifs.close();
		printf("\n\n");
	}



}