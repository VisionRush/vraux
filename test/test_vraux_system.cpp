#include "test.h"

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