#include "vraux/vraux_system.h"

namespace visionrush
{
	string VRSystemTool::GetTime(string format)
	{
		char timebuf[255];
		time_t timevalue;
		time(&timevalue);

		strftime(timebuf, 255, format.c_str(), localtime(&timevalue));

		// %Y-%m-%d %H:%M:%S
		// %Y/%m/%d\t%H:%M:%S
		// %Y/%m/%d\t%I:%M:%S %p

		return timebuf;
	}

	int VRSystemTool::FindProcess(string proc_name)
	{
		int proc_num = 0;
#if defined Q_OS_WIN
		// create proc snapshot
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		HANDLE procsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (procsnap == INVALID_HANDLE_VALUE)
		{
			printf("libvr: create proc snapshot failed.\n");
			return 0;
		}
		// traverse proc info
		BOOL suc = ::Process32First(procsnap, &pe32);
		while (suc)
		{
			if (0 == _stricmp(proc_name.c_str(), pe32.szExeFile))
				proc_num += 1;
			suc = ::Process32Next(procsnap, &pe32);
		}
#elif defined Q_OS_LINUX
		// create pipe
		string cmd = "ps -ef | grep " + proc_name + " | grep -v grep";
		FILE *pp = popen(cmd.c_str(), "r");
		// check
		if (pp == NULL)	return -1;
		// get proc info
		char buff[1024];
		vector<string> vec_procinfo;
		while (fgets(buff, sizeof(buff), pp) != NULL) {
			if (buff[strlen(buff) - 1] == '\n')
				buff[strlen(buff) - 1] = '\0';
			vec_procinfo.push_back(buff);
		}
		// amalyze proc info
		for (size_t i = 0; i < vec_procinfo.size(); i++)
		{
			if (vec_procinfo[i].find(proc_name) == vec_procinfo[i].find(proc_name + " "))
				proc_num++;
		}
#else
#endif
		// return
		return proc_num;
	}

	void VRSystemTool::Logf(string logpath, const char *format, ...)
	{
		// format text with variable-argument
		va_list arg;
		va_start(arg, format);
		char logbuff[4096];
		vsprintf(logbuff, format, arg);
		va_end(arg);
		// add time
		char currenttimebuff[255];
		time_t currenttime = time(NULL);
		strftime(currenttimebuff, 255, "%Y-%m-%d %H:%M:%S", localtime(&currenttime));
		// print screen
		printf("[%s] %s", currenttimebuff, logbuff);
		// print log file
		std::ofstream ofs(logpath, ios::app);
		ofs << "[" << currenttimebuff << "] " << logbuff;
		ofs.close();
	}

	string VRSystemTool::CalcMD5ofString(string text)
	{
		return h_md5_.calcmd5_string(text);
	}

	string VRSystemTool::CalcMD5ofFile(string filepath)
	{
		return h_md5_.calcmd5_file(filepath);
	}

	string VRSystemTool::CalcSHA1ofString(string text)
	{
		string out_sha1value;
		// calc
		h_sha1_.Update((UINT_8*)text.c_str(), text.size() * sizeof(TCHAR));
		h_sha1_.Final();
		h_sha1_.ReportHashStl(out_sha1value, VRCSHA1::REPORT_HEX_SHORT);
		h_sha1_.Reset();
		// return
		transform(out_sha1value.begin(), out_sha1value.end(), out_sha1value.begin(), ::tolower);  
		return out_sha1value;
	}

	string VRSystemTool::CalcSHA1ofFile(string filepath)
	{
		string out_sha1value;
		// calc
		const bool bsuc= h_sha1_.HashFile(filepath.c_str());
		h_sha1_.Final();
		h_sha1_.ReportHashStl(out_sha1value, VRCSHA1::REPORT_HEX_SHORT);
		if (!bsuc) out_sha1value = "";
		h_sha1_.Reset();
		// return
		transform(out_sha1value.begin(), out_sha1value.end(), out_sha1value.begin(), ::tolower);  
		return out_sha1value;
	}

	string VRSystemTool::Encrypt(string input_text, int key[])
	{ 
		int keylen = sizeof(key) / sizeof(key[0]);
		string output_text = input_text;
		for(int i = 0, j = 0; output_text[j]; j++, i=(i+1)%keylen)
		{
			output_text[j] += key[i];
			if(output_text[j] > 122) output_text[j] -= 90;
		}
		return output_text;
	}

	string VRSystemTool::Encrypt(string input_text, const char* key)
	{
		int keylen = strlen(key);
		string output_text = input_text;
		for(int i = 0, j = 0; output_text[j]; j++, i=(i+1)%keylen)
		{
			output_text[j] += key[i];
			if(output_text[j] > 122) output_text[j] -= 90;
		}
		return output_text;
	}

	string VRSystemTool::Decrypt(string input_text,int key[])
	{ 
		int keylen = sizeof(key) / sizeof(key[0]);
		string output_text = input_text;
		for(int i = 0, j = 0; output_text[j];j++, i=(i+1)%keylen)
		{
			output_text[j] -= key[i];
			if(output_text[j] < 32) output_text[j] += 90;
		}
		return output_text;
	}

	string VRSystemTool::Decrypt(string input_text, const char* key)
	{
		int keylen = strlen(key);
		string output_text = input_text;
		for(int i = 0, j = 0; output_text[j];j++, i=(i+1)%keylen)
		{
			output_text[j] -= key[i];
			if(output_text[j] < 32) output_text[j] += 90;
		}
		return output_text;
	}

	void VRSystemTool::EncryptFilevr(string in_filename, string out_filename, const char *pwd)
	{
		// check
		int len_pwd = strlen(pwd);
		// open ori-file
		FILE *fp1, *fp2;
		fp1 = fopen(in_filename.c_str(), "rb+");
		if (fp1 == NULL)
		{
			printf("libvr: cannot open in-file.\n");
			return;
		}
		// open dst-file
		fp2 = fopen(out_filename.c_str(), "wb+");
		if (fp2 == NULL)
		{
			printf("libvr: cannot open or create out-file.\n");
			return;
		}
		// preprocess
		register char ch;
		int j = 0;
		int j0 = 0;
		// encrypt
		ch = fgetc(fp1);
		while (!feof(fp1))
		{
			if (j0 > len_pwd) j0 = 0;
			ch += pwd[j0++];
			fputc(ch, fp2);
			ch = fgetc(fp1);
		}
		// close
		fclose(fp1);
		fclose(fp2);
	}

	void VRSystemTool::DecryptFilevr(string in_filename, string out_filename, const char *pwd)
	{
		// check
		int len_pwd = strlen(pwd);
		// open ori-file
		FILE *fp1, *fp2;
		fp1 = fopen(in_filename.c_str(), "rb+");
		if (fp1 == NULL)
		{
			printf("libvr: cannot open in-file.\n");
			return;
		}
		// open dst-file
		fp2 = fopen(out_filename.c_str(), "wb+");
		if (fp2 == NULL)
		{
			printf("libvr: cannot open or create out-file.\n");
			return;
		}
		// preprocess
		register char ch;
		int j = 0;
		int j0 = 0;
		// decrypt
		ch = fgetc(fp1);
		while (!feof(fp1))
		{
			if (j0 > len_pwd) j0 = 0;
			ch -= pwd[j0++];
			fputc(ch, fp2);
			ch = fgetc(fp1);
		}
		// close
		fclose(fp1);
		fclose(fp2);
	}

}