#ifndef __VRAUX_STRINGPROCESS_H__
#define __VRAUX_STRINGPROCESS_H__
#include "vraux/vraux_header.h"

namespace visionrush
{
	class VR_API VRStringProcTool
	{
	public:
		VRStringProcTool() = default;

		// Func: 
		//	Split string with specified separator.
		// Input:
		//	string str					: string
		//	char delim					: delimiter
		// Output:
		//	vector<string>& vec_item	: separated item
		void Split(string str, char delim, vector<string>& vec_item);

		// Func: 
		//	Split string with specified separator.
		// Input:
		//	string str					: string
		//	char delim					: delimiter
		// Output:
		//	vector<string>& vec_item	: separated item
		void Split(string str, string delim, vector<string>& vec_item);

		// Func:
		//	Replace specified ori-words with dst-words.
		// Input:
		//	string& input_str		: input string
		//	const string& ori_words	: ori words(be replcaed)
		//	const string& dst_words	: dst words
		// Output:
		//	string& output_str		: output string
		void Replace(string& input_str, string& output_str, const string& ori_words, const string& dst_words);

		// Func:
		//	Convert string-code from utf-8 to gb2312(ansi).
		// Input:
		//	string& input_str	: inpute string
		// Output:
		//	string& output_str	: output string
		void UTF8ToGB(string& input_str, string& output_str);
	
		// Func:
		//	Check file code format. could not recognize utf-8 without bom.
		// Input:
		//	string filepath		: file path
		// Return:
		//	string				: code format
		string CheckFileCodeformat(string filepath);

	};
}

#endif	// __VRAUX_STRINGPROCESS_H__