#include "test.h"

void TestForFileSystem()
{
	printf("***************************************************\n");
	printf("*                                                 *\n");
	printf("*           Module: vraux_filesystemvr            *\n");
	printf("*                                                 *\n");
	printf("***************************************************\n\n");

	VRFileSystemTool vrtool;

	// -----------------------------------------------
	// Test for File/Dir Traverse
	// -----------------------------------------------
	{
		string dir;
		vector<string> filenames;
#if defined Q_OS_WIN
		dir = "C:\\opencv2410\\include\\opencv2";
#elif defined Q_OS_LINUX
		dir = "/usr/include/opencv2";
#else
#endif
		// 1
		printf("libvr: TraverseFileNamesRecursively(*.h).\n");
		printf("------------------------------------------\n");
		filenames.clear();
		vrtool.TraverseFileNamesRecursively(dir, filenames, "*.h");
		for (size_t i = 0; i < filenames.size(); i++)
			printf("%s\n", filenames[i].c_str());
		printf("\n\n");

		// 2
		printf("libvr: TraverseFilePathes(*.hpp).\n");
		printf("------------------------------------------\n");
		filenames.clear();
		vrtool.TraverseFilePathes(dir, filenames, "*.hpp");
		for (size_t i = 0; i < filenames.size(); i++)
			printf("%s\n", filenames[i].c_str());
		printf("\n\n");

		// 3
		printf("libvr: TraverseSubDirectoryNames.\n");
		printf("------------------------------------------\n");
		filenames.clear();
		vrtool.TraverseSubDirectoryNames(dir, filenames);
		for (size_t i = 0; i < filenames.size(); i++)
			printf("%s\n", filenames[i].c_str());
		printf("\n\n");
	}

	// -----------------------------------------------
	// Test for Path Check
	// -----------------------------------------------
	{
		string dir;
		string normdir;
		string path;
		string normpath;
		string name;

#if defined Q_OS_WIN
		dir = "C:\\opencv2410\\include\\opencv2";
		path = "C:\\opencv2410/include\\opencv2\\opencv.hpp";
#elif defined Q_OS_LINUX
		dir = "/usr/include/opencv2";
		path = "/usr/include/opencv2/opencv.hpp";
#else
#endif
		// normalize path
		printf("libvr: NormalizePath.\n");
		printf("------------------------------------------\n");
		vrtool.NormalizePath(dir, normdir);
		printf("libvr: %s ---> %s \n", dir.c_str(), normdir.c_str());
		vrtool.NormalizePath(path, normpath);
		printf("libvr: %s ---> %s \n", path.c_str(), normpath.c_str());
		printf("\n\n");

		// check file type
		printf("libvr: IsFile/IsDirectory.\n");
		printf("------------------------------------------\n");
		if (vrtool.IsFile(normpath))
			printf("libvr: %-42s is a file.\n", normpath.c_str());
		if (vrtool.IsDirectory(normpath))
			printf("libvr: %-42s is a directory.\n", normpath.c_str());
		if (vrtool.IsFile(normdir))
			printf("libvr: %-42s is a file.\n", normdir.c_str());
		if (vrtool.IsDirectory(normdir))
			printf("libvr: %-42s is a directory.\n", normdir.c_str());
		printf("\n\n");

		// check file size
		printf("libvr: GetFileSizeX \n");
		printf("------------------------------------------\n");
		printf("libvr: %s size is %lld \n", normpath.c_str(), vrtool.GetFileSizeX(normpath));
		printf("\n\n");


		// get file name
		name = vrtool.GetFileName(path);
		printf("libvr: GetFileName \n");
		printf("------------------------------------------\n");
		printf("libvr: path is %s \n", path.c_str());
		printf("libvr: name is %s \n", name.c_str());
		printf("\n\n");

		// get file extension
		string extension;
		extension = vrtool.GetFileExtension(path);
		printf("libvr: GetFileExtension \n");
		printf("------------------------------------------\n");
		printf("libvr: path is %s \n", path.c_str());
		printf("libvr: ext  is %s \n", extension.c_str());
		printf("\n\n");

		// get file name without extension
		name = vrtool.GetFileNameWithoutExtension(path);
		printf("libvr: GetFileNameWithoutExtension \n");
		printf("------------------------------------------\n");
		printf("libvr: path is %s \n", path.c_str());
		printf("libvr: name(no ext) is %s.\n", name.c_str());
		printf("\n\n");

		// get file path without extension
		name = vrtool.GetFilePathWithoutExtension(path);
		printf("libvr: GetFilePathWithoutExtension \n");
		printf("------------------------------------------\n");
		printf("libvr: path is %s \n", path.c_str());
		printf("libvr: path(no ext) is %s \n", name.c_str());
		printf("\n\n");

		// get file-dir name
		name = vrtool.GetFileDirectoryName(path);
		printf("libvr: GetFileDirectoryName \n");
		printf("------------------------------------------\n");
		printf("libvr: path is %s \n", path.c_str());
		printf("libvr: name is %s \n", name.c_str());
		printf("\n\n");

		// get dir name
		name = vrtool.GetDirectoryName(dir);
		printf("libvr: GetDirectoryName \n");
		printf("------------------------------------------\n");
		printf("libvr: dir  is %s \n", dir.c_str());
		printf("libvr: name is %s \n", name.c_str());
		printf("\n\n");

	}
}

void TestForSystem()
{
	printf("***************************************************\n");
	printf("*                                                 *\n");
	printf("*              Module: vraux_system               *\n");
	printf("*                                                 *\n");
	printf("***************************************************\n\n");

	VRSystemTool vrtool;

	// -----------------------------------------------
	// Test for Time
	// -----------------------------------------------
	{
		printf("libvr: GetTime.\n");
		printf("------------------------------------------\n");
		// get time
		printf("libvr: %s \n", vrtool.GetTime().c_str());
		printf("libvr: %s \n", vrtool.GetTime("%Y/%m/%d %H-%M-%S").c_str());
		printf("libvr: %s \n", vrtool.GetTime("%Y/%m/%d").c_str());
		printf("\n\n");
	}

	// -----------------------------------------------
	// Test for Process Check
	// -----------------------------------------------
	{
		printf("libvr: FindProcess.\n");
		printf("------------------------------------------\n");
		// find proc
		int proc_num = 0;
#if defined Q_OS_WIN
		string proc_name = "chrome.exe";
#elif defined Q_OS_LINUX
		string proc_name = "img_cmp";
#else
#endif
		proc_num = vrtool.FindProcess(proc_name);
		printf("libvr: proc %s number is %d.\n", proc_name.c_str(), proc_num);
		printf("\n\n");
	}

	// -----------------------------------------------
	// Test for Simple Log
	// -----------------------------------------------
	{
		printf("libvr: Logf.\n");
		printf("------------------------------------------\n");
		// log
		vrtool.Logf("vrlog.txt", "libvr: hello %s.\n", "world");
		vrtool.Logf("vrlog.txt", "libvr: this is a %s log info.\n", "simple");
		printf("\n\n");
	}

	// -----------------------------------------------
	// Test for MD5 & SHA1
	// -----------------------------------------------
	{
		printf("libvr: CalcMD5 & CalcSHA1.\n");
		printf("------------------------------------------\n");
		// string md5 & sha1
		string cleartext = "hello world!";
		string md5text;
		string sha1text;
		md5text = vrtool.CalcMD5ofString(cleartext);
		sha1text = vrtool.CalcSHA1ofString(cleartext);
		printf("libvr: clear-text: %-16s, md5  is %s \n", cleartext.c_str(), md5text.c_str());
		printf("libvr: clear-text: %-16s, sha1 is %s \n", cleartext.c_str(), sha1text.c_str());
		cleartext = "vision rush!";
		md5text = vrtool.CalcMD5ofString(cleartext);
		sha1text = vrtool.CalcSHA1ofString(cleartext);
		printf("libvr: clear-text: %-16s, md5  is %s \n", cleartext.c_str(), md5text.c_str());
		printf("libvr: clear-text: %-16s, sha1 is %s \n", cleartext.c_str(), sha1text.c_str());

		// file md5 & sha1
		string filepath = "wangbo.jpg";
		md5text = vrtool.CalcMD5ofFile(filepath);
		sha1text = vrtool.CalcSHA1ofFile(filepath);
		printf("libvr: file-path : %-16s, md5  is %s \n", filepath.c_str(), md5text.c_str());
		printf("libvr: file-path : %-16s, sha1 is %s \n", filepath.c_str(), sha1text.c_str());
		printf("\n\n");
	}

	// -----------------------------------------------
	// Test for Encrypt & Decrypt
	// -----------------------------------------------
	{
		printf("libvr: Encrypt-String & Decrypt-String.\n");
		printf("------------------------------------------\n");
		// encrypt and decrypt string
		string input_text = "Hello, world!";
		string encrypted_text;
		string decrypted_text;
		int    skey[] = { 4, 9, 6, 2, 8, 7, 3 };
		int	   skeylen = sizeof(skey) / sizeof(skey[0]);
		char   pwd[11] = "1234567890";
		int    pwdlen = strlen(pwd);

		encrypted_text = vrtool.Encrypt(input_text, skey);
		decrypted_text = vrtool.Decrypt(encrypted_text, skey);
		printf("libvr: clear-text: %-24s, e-text is %-24s, d-text is %s.\n", input_text.c_str(), encrypted_text.c_str(), decrypted_text.c_str());

		input_text = "vision rush!";
		encrypted_text = vrtool.Encrypt(input_text, skey);
		decrypted_text = vrtool.Decrypt(encrypted_text, skey);
		printf("libvr: clear-text: %-24s, e-text is %-24s, d-text is %s.\n", input_text.c_str(), encrypted_text.c_str(), decrypted_text.c_str());

		input_text = "wow! happy happy!!";
		encrypted_text = vrtool.Encrypt(input_text, pwd);
		decrypted_text = vrtool.Decrypt(encrypted_text, pwd);
		printf("libvr: clear-text: %-24s, e-text is %-24s, d-text is %s.\n", input_text.c_str(), encrypted_text.c_str(), decrypted_text.c_str());
		printf("\n\n");


		printf("libvr: Encrypt-File & Decrypt-File.\n");
		printf("------------------------------------------\n");
		// encrypt and decrypt file
		string input_file = "wangbo.jpg";
		string encrypted_file = "wangbo_enc.jpg";
		string decrypted_file = "wangbo_dec.jpg";

		vrtool.EncryptFilevr(input_file, encrypted_file, pwd);
		vrtool.DecryptFilevr(encrypted_file, decrypted_file, pwd);
		printf("\n\n");
	}

}

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

