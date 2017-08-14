#include "vraux/vraux_stringprocess.h"

namespace visionrush
{
	void VRStringProcTool::Split(string str, char delim, vector<string>& vec_item)
	{
		stringstream ss(str);
		string item;
		while (getline(ss, item, delim))
			vec_item.push_back(item);
	}

	void VRStringProcTool::Split(string str, string delim, vector<string>& vec_item)
	{
		const int len = strlen(delim.c_str());
		size_t index = 0;
		size_t pos = str.find(delim, index);
		while (pos != string::npos)
		{
			string item = str.substr(index, pos - index);
			vec_item.push_back(item);
			index = pos + len;
			pos = str.find(delim, index);
		}
		if ((index + 1) <= str.length())
		{
			string item = str.substr(index, str.length() - index);
			vec_item.push_back(item);
		}
	}

	void VRStringProcTool::Replace(string& input_str, string& output_str, const string& ori_words, const string& dst_words)
	{
		// set output
		output_str = input_str;
		// replace
		string::size_type pos = 0;
		string::size_type ori_len = ori_words.size();
		string::size_type dst_len = dst_words.size();
		while ((pos = output_str.find(ori_words, pos)) != string::npos)
		{
			// way1
			output_str.replace(pos, ori_len, dst_words);
			pos += dst_len;
		}
	}

	void VRStringProcTool::UTF8ToGB(string& input_str, string& output_str)
	{
		if (input_str.length() == 0) return;
#if defined Q_OS_WIN

		WCHAR*	dst_unicodebuff;
		DWORD 	dst_unicodebufflen;
		// ----------------------------
		// convert input_str to unicode
		// ----------------------------
		// get dst buff length
		dst_unicodebufflen = MultiByteToWideChar(CP_UTF8, 0, input_str.c_str(), -1, NULL, 0);
		// convert to WCHAR(unicode)
		dst_unicodebuff = new WCHAR[dst_unicodebufflen];
		MultiByteToWideChar(CP_UTF8, 0, input_str.c_str(), -1, dst_unicodebuff, dst_unicodebufflen);

		// ----------------------------
		// convert unicode to ansi
		// ----------------------------
		LPSTR	dst_ansibuff;
		DWORD 	dst_ansibufflen;
		// get dst buff length
		dst_ansibufflen = WideCharToMultiByte(CP_ACP, 0, dst_unicodebuff, -1, NULL, 0, NULL, FALSE);
		// convert to char(ansi)
		dst_ansibuff = new CHAR[dst_ansibufflen + 1];
		int nRet = WideCharToMultiByte(CP_ACP, 0, dst_unicodebuff, -1, dst_ansibuff, dst_ansibufflen, NULL, FALSE);

		// set output_str
		output_str = dst_ansibuff;
		delete[]dst_unicodebuff;
		delete[]dst_ansibuff;

#elif defined Q_OS_LINUX
		output_str = input_str;
#else
#endif
		// post-process
		if (output_str[0] == '?') output_str.erase(0, 1);
		if (output_str[0] == ' ') output_str.erase(0, 1);

	}

	string VRStringProcTool::CheckFileCodeformat(string filepath)
	{
		unsigned char temp_c;
		int		code_int;
		string	code_str;
		// read first char
		ifstream fin(filepath, ios::binary);
		fin.read((char*)&temp_c, sizeof(temp_c));
		// left 8 bit
		code_int = temp_c << 8;
		// read second char
		fin.read((char*)&temp_c, sizeof(temp_c));
		// create code in int
		code_int += temp_c;
		// create code in streing
		switch (code_int)
		{
		case 0xfffe:	// 65534  
			code_str = "Unicode";
			break;
		case 0xfeff:	// 65279  
			code_str = "Unicode big endian";
			break;
		case 0xefbb:	// 61371  
			code_str = "UTF-8 with BOM";
			break;
		default:
			code_str = "ANSI";
		}
		fin.close();

		return code_str;
	}
}