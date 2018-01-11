#include "test.h"

void TestForFileSystem()
{
	printf("***************************************************\n");
	printf("*                                                 *\n");
	printf("*           Module: vraux_filesystem              *\n");
	printf("*                                                 *\n");
	printf("***************************************************\n\n");

	VRFileSystemTool vrtool;

	// -----------------------------------------------
	// Test for File/Dir Traverse
	// -----------------------------------------------
	{
		string dirpath;
		vector<string> filenames;
#if defined Q_OS_WIN
		dirpath = "./";
#elif defined Q_OS_LINUX
		dirpath = "./";
#else
#endif

		// 1
		printf("libvr: TraverseFileNamesRecursively(*.txt).\n");
		printf("------------------------------------------\n");
		filenames.clear();
		vrtool.TraverseFileNamesRecursively(dirpath, filenames, "*.txt");
		for (size_t i = 0; i < filenames.size(); i++)
			printf("%s\n", filenames[i].c_str());
		printf("\n\n");

		// 2
		printf("libvr: TraverseFilePathes(*.txt).\n");
		printf("------------------------------------------\n");
		filenames.clear();
		vrtool.TraverseFilePathes(dirpath, filenames, "*.txt");
		for (size_t i = 0; i < filenames.size(); i++)
			printf("%s\n", filenames[i].c_str());
		printf("\n\n");

		// 3
		printf("libvr: TraverseSubDirectoryNames.\n");
		printf("------------------------------------------\n");
		filenames.clear();
		vrtool.TraverseSubDirectoryNames(dirpath, filenames);
		for (size_t i = 0; i < filenames.size(); i++)
			printf("%s\n", filenames[i].c_str());
		printf("\n\n");
	}



	// -----------------------------------------------
	// Test for Path Check
	// -----------------------------------------------
	{
		string dirpath;
		string normdir;
		string filepath;
		string normpath;
		string name;

#if defined Q_OS_WIN
		dirpath = "C:\\opencv2410\\include\\opencv2";
		filepath = "C:\\opencv2410/include\\opencv2\\opencv.hpp";
#elif defined Q_OS_LINUX
		dirpath = "/usr/include/opencv2";
		filepath = "/usr//include\\opencv2/opencv.hpp";
#else
#endif
		// normalize path
		printf("libvr: NormalizePath.\n");
		printf("------------------------------------------\n");
		vrtool.NormalizePath(dirpath, normdir);
		printf("libvr: %s ---> %-64s \n", dirpath.c_str(), normdir.c_str());
		vrtool.NormalizePath(filepath, normpath);
		printf("libvr: %s ---> %-64s \n", filepath.c_str(), normpath.c_str());
		printf("\n\n");


		// check current directory
		dirpath = vrtool.GetPWD();
		printf("libvr: GetPWD.\n");
		printf("------------------------------------------\n");
		printf("libvr: pwd is %s\n", dirpath.c_str());
		printf("\n\n");


		// check file type
		printf("libvr: IsFile/IsDirectory.\n");
		printf("------------------------------------------\n");
		filepath = dirpath + "wangbo.txt";
		vrtool.NormalizePath(dirpath, normdir);
		vrtool.NormalizePath(filepath, normpath);
		
		if (vrtool.IsFile(normpath))
			printf("libvr: %-64s is a file.\n", normpath.c_str());
		if (vrtool.IsDirectory(normpath))
			printf("libvr: %-64s is a directory.\n", normpath.c_str());
		if (vrtool.IsFile(normdir))
			printf("libvr: %-64s is a file.\n", normdir.c_str());
		if (vrtool.IsDirectory(normdir))
			printf("libvr: %-64s is a directory.\n", normdir.c_str());
		printf("\n\n");

		// check file size
		printf("libvr: GetFileSizeX \n");
		printf("------------------------------------------\n");
		printf("libvr: %s size is %lld Byte \n", normpath.c_str(), vrtool.GetFileSizeX(normpath));
		printf("\n\n");


		// get file name
		filepath = dirpath + "wangbo";
		name = vrtool.GetFileName(filepath);
		printf("libvr: GetFileName \n");
		printf("------------------------------------------\n");
		printf("libvr: path is %s \n", filepath.c_str());
		printf("libvr: name is %s \n", name.c_str());
		printf("\n\n");

		// get file extension
		string extension;
		extension = vrtool.GetFileExtension(filepath);
		printf("libvr: GetFileExtension \n");
		printf("------------------------------------------\n");
		printf("libvr: path is %s \n", filepath.c_str());
		printf("libvr: ext  is %s \n", extension.c_str());
		printf("\n\n");

		// get file name without extension
		name = vrtool.GetFileNameWithoutExtension(filepath);
		printf("libvr: GetFileNameWithoutExtension \n");
		printf("------------------------------------------\n");
		printf("libvr: path is %s \n", filepath.c_str());
		printf("libvr: name(no ext) is %s.\n", name.c_str());
		printf("\n\n");

		// get file path without extension
		name = vrtool.GetFilePathWithoutExtension(filepath);
		printf("libvr: GetFilePathWithoutExtension \n");
		printf("------------------------------------------\n");
		printf("libvr: path is %s \n", filepath.c_str());
		printf("libvr: path(no ext) is %s \n", name.c_str());
		printf("\n\n");

		// get file-dir name
		name = vrtool.GetFileDirectoryName(filepath);
		printf("libvr: GetFileDirectoryName \n");
		printf("------------------------------------------\n");
		printf("libvr: path is %s \n", filepath.c_str());
		printf("libvr: name is %s \n", name.c_str());
		printf("\n\n");

		// get dir name
		name = vrtool.GetDirectoryName(dirpath);
		printf("libvr: GetDirectoryName \n");
		printf("------------------------------------------\n");
		printf("libvr: dir  is %s \n", dirpath.c_str());
		printf("libvr: name is %s \n", name.c_str());
		printf("\n\n");

	}

	// -----------------------------------------------
	// Test for Read line from text
	// -----------------------------------------------
	{
		string filepath;
		vector<string> lines;
		filepath = "wangbo.txt";
		vrtool.ReadLineFromTxt(filepath, lines);
		printf("libvr: ReadLineFromTxt \n");
		printf("------------------------------------------\n");
		printf("libvr: line number is %d.\n", lines.size());
		printf("\n\n");
	}

	// -----------------------------------------------
	// Test for Remove Directory
	// -----------------------------------------------
	{
		/*
	string dirpath;
	// create dir
	dirpath = "test";
	//vrtool.CreateDirectoryx(dirpath);
	// create file

	int state = vrtool.RemoveDirectoryx(dirpath, 0);
	printf("libvr: %d\n", state);
	*/
	}

	// -----------------------------------------------
	// Test for Copy file & Move file & Remove file
	// -----------------------------------------------
	{
		string src_path;
		string dst_path;

		// copy file
		src_path = "wangbo.txt";
		dst_path = "wangbo_copy.txt";
		int state = vrtool.CopyFilex(src_path, dst_path, true);
		printf("libvr: CopyFilex \n");
		printf("------------------------------------------\n");
		if (state == 0)
			printf("libvr: copy %s success!\n", src_path.c_str());
		else
			printf("libvr: copy %s failure!\n", src_path.c_str());
		printf("\n\n");

		// move file
		src_path = "wangbo_copy.txt";
		dst_path = "wangbo_move.txt";
		state = vrtool.MoveFilex(src_path, dst_path);
		printf("libvr: MoveFilex \n");
		printf("------------------------------------------\n");
		if (state == 0)
			printf("libvr: move %s success!\n", src_path.c_str());
		else
			printf("libvr: move %s failure!\n", src_path.c_str());
		printf("\n\n");

		// remove file
		state = vrtool.RemoveFile(dst_path);
		printf("libvr: RemoveFile \n");
		printf("------------------------------------------\n");
		if (state == 0)
			printf("libvr: remove %s success!\n", dst_path.c_str());
		else
			printf("libvr: remove %s failure!\n", dst_path.c_str());
		printf("\n\n");

		// create dir
		string dirpath;
		dirpath = "visionrush";
		state = vrtool.CreateDirectoryx(dirpath);
		printf("libvr: CreateDirectoryx \n");
		printf("------------------------------------------\n");
		if (state == 0)
			printf("libvr: create %s success!\n", dirpath.c_str());
		else
			printf("libvr: create %s failure!\n", dirpath.c_str());
		printf("\n\n");

		// remove dir
		state = vrtool.RemoveDirectoryx(dirpath);
		printf("libvr: RemoveDirectoryx \n");
		printf("------------------------------------------\n");
		if (state == 0)
			printf("libvr: remove %s success!\n", dirpath.c_str());
		else
			printf("libvr: remove %s failure!\n", dirpath.c_str());
		printf("\n\n");
	}

}





