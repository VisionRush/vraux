#ifndef __VRAUX_FILESYSTEM_H__
#define __VRAUX_FILESYSTEM_H__
#include "vraux_header.h"

namespace visionrush
{
	class VRFileSystemTool 
	{
	public:
		VRFileSystemTool() = default;

		// Func:
		//	Traverse all file name in specialed directory.
		// Input:
		//	string dir					: specialed directory
		//	string extension			: extension, default is *.*
		// Output:
		//	vector<string>& filenames	: file name vector
		void TraverseFileNames(string dir, vector<string>& filenames, string extension = "*.*");

		// Func:
		//	Traverse all file name in specialed directory recursively.
		// Input:
		//	string dir					: specialed directory
		//	string extension			: extension, default is *.*
		// Output:
		//	vector<string>& filenames	: file name vector
		void TraverseFileNamesRecursively(string dir, vector<string>& filenames, string extension = "*.*");

		// Func:
		//	Traverse all file path in specialed directory.
		// Input:
		//	string dir					: specialed directory
		//	string extension			: extension, default is *.*
		// Output:
		//	vector<string>& filepathes	: file path vector
		void TraverseFilePathes(string dir, vector<string>& filepathes, string extension = "*.*");

		// Func:
		//	Traverse all file path in specialed directory recursively.
		// Input:
		//	string dir					: specialed directory
		//	string extension			: extension, default is *.*
		// Output:
		//	vector<string>& filepathes	: file path vector
		void TraverseFilePathesRecursively(string dir, vector<string>& filepathes, string extension = "*.*");

		// Func:
		//	Traverse sub directory name in speciald directory.
		// Input:
		//	string dir						: specialed directory
		// Output:
		//	vector<string>& subdirnames		: sub directory name vector
		void TraverseSubDirectoryNames(string dir, vector<string>& subdirnames);

		// Func:
		//	Traverse sub directory path in speciald directory.
		// Input:
		//	string dir						: specialed directory
		// Output:
		//	vector<string>& subdirpathes	: sub directory path vector
		void TraverseSubDirectoryPathes(string dir, vector<string>& subdirpathes);

		// Func:
		//	Normalize path, that is, convert path format to unix/linux mode.
		// Input:
		//	string input_path	:	intput path(any format)
		// Output:
		//	string& output_path	:	output path(unix/linux format)
		void NormalizePath(string input_path, string& output_path);

		// Func:
		//	Check if it is a directory.
		// Input:
		//	string input_path	: input path
		// Return:
		//	bool				: true or false
		bool IsDirectory(string input_path);

		// Func:
		//	Check if it is a file.
		// Input:
		//	string input_path	: input path
		// Return:
		//	bool				: true or false
		bool IsFile(string input_path);

		// Func:
		//	Check if exist.
		// Input:
		//	string input_path	: input path
		// Return:
		//	bool				: true or false
		bool Exist(string input_path);

		// Func:
		//	Get file size.
		// Input:
		//	string filepath	: file path
		// Return:
		//	long long		: file size
		long long GetFileSizeX(string filepath);


	private:

		// Func:
		//	Traverse name/path in specialed directory.
		// Input:
		//	string dir					: specialed directory
		//	string extension			: extension, e.g. *.*, *.jpg
		//	int type					: 0: get name, 1: get path, 2: get subdir name, 3: get subdir path
		//	bool recursive				: true: recursive, false: no-recursive
		// Output:
		//	vector<string>& filenames	: file name vector
		void Traverse(string dir, vector<string>& filenames, string extension, int type, bool recursive);

	};
}


#endif // __VRAUX_FILESYSTEM_H__