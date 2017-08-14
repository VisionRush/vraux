#ifndef __VRAUX_SYSTEM_H__
#define __VRAUX_SYSTEM_H__
#include "vraux/vraux_header.h"
#include "vraux/vraux_md5.h"
#include "vraux/vraux_sha1.h"

namespace visionrush
{
	class VR_API VRSystemTool
	{
	public:
		VRSystemTool() = default;

		// Func:
		//	Get current local time.
		// Input:
		//	string format	: time format, e.g., "%Y-%m-%d %H:%M:%S", "%Y/%m/%d\t%I:%M:%S %p"
		// Return:
		//	string			: time
		string GetTime(string format = "%Y-%m-%d %H:%M:%S");

		// Func:
		//	Find if the process exists.
		// Input:
		//	string proc_name	: proc name
		// Return:
		//	int					: proc number
		int FindProcess(string proc_name);
	
		// Func:
		//	Record program log.
		// Input:
		//	string logpath		: log file path
		//	const char *format	: format
		//	...					: variable-argument
		void Logf(string logpath, const char *format, ...);

		// Func:
		//	Calculate md5 for text.
		// Input:
		//	string text		: clear text
		// Return:
		//	string			: md5 text
		string CalcMD5ofString(string text);

		// Func:
		//	Calculate md5 for file.
		// Input:
		//	string filepath	: file path
		// Return:
		//	string			: md5 text
		string CalcMD5ofFile(string filepath);

		// Func:
		//	Calculate sha1 for text.
		// Input:
		//	string text		: clear text
		// Return:
		//	string			: sha1 text
		string CalcSHA1ofString(string text);

		// Func:
		//	Calculate sha1 for file.
		// Input:
		//	string filepath	: file path
		// Return:
		//	string			: sha1 text
		string CalcSHA1ofFile(string filepath);

		// Func:
		//	Encrypt text.
		// Input:
		//	string input_text	: input clear text
		//	int key[]			: secret key
		// Return:
		//	string				: encrypted text
		string Encrypt(string input_text, int key[]);
		// Func:
		//	Encrypt text.
		// Input:
		//	string input_text	: input clear text
		//	const char* key		: secret key
		// Return:
		//	string				: encrypted text
		string Encrypt(string input_text, const char* key);

		// Func:
		//	Decrypt text.
		// Input:
		//	string input_text	: input encrypted text
		//	int key[]			: secret key
		// Return:
		//	string				: decrypted text
		string Decrypt(string input_text, int key[]);
		// Func:
		//	Decrypt text.
		// Input:
		//	string input_text	: input encrypted text
		//	const char* key		: secret key
		// Return:
		//	string				: decrypted text
		string Decrypt(string input_text, const char* key);

		// Func:
		//	Encrypt file with a password.
		// Input:
		//	string in_filename		: input file	
		//	string out_filename		: output file
		//	const char *pwd			: secret key
		void EncryptFilevr(string in_filename, string out_filename, const char *pwd);

		// Func:
		//	Decrypt file with a password.
		// Input:
		//	string in_filename		: input file	
		//	string out_filename		: output file
		//	const char *pwd			: secret key
		void DecryptFilevr(string in_filename, string out_filename, const char *pwd);

	private:
		MD5 h_md5_;
		CSHA1 h_sha1_;
	};

}

#endif	// __VRAUX_SYSTEM_H__



// process check