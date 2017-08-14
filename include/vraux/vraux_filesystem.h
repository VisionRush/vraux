#ifndef __VRAUX_FILESYSTEM_H__
#define __VRAUX_FILESYSTEM_H__
#include "vraux/vraux_header.h"

namespace visionrush
{
	class VR_API VRFileSystemTool 
	{
	public:
		VRFileSystemTool() = default;

		// Func:
		//	Traverse all file name in specialed directory.
		// Input:
		//	dir				: specialed directory
		//	extension		: extension, default is *.*
		// Output:
		//	filenames		: file name vector
		void TraverseFileNames(string dir, vector<string>& filenames, string extension = "*.*");

		// Func:
		//	Traverse all file name in specialed directory recursively.
		// Input:
		//	dir				: specialed directory
		//	extension		: extension, default is *.*
		// Output:
		//	filenames		: file name vector
		void TraverseFileNamesRecursively(string dir, vector<string>& filenames, string extension = "*.*");

		// Func:
		//	Traverse all file path in specialed directory.
		// Input:
		//	dir				: specialed directory
		//	extension		: extension, default is *.*
		// Output:
		//	filepathes		: file path vector
		void TraverseFilePathes(string dir, vector<string>& filepathes, string extension = "*.*");

		// Func:
		//	Traverse all file path in specialed directory recursively.
		// Input:
		//	dir				: specialed directory
		//	extension		: extension, default is *.*
		// Output:
		//	filepathes		: file path vector
		void TraverseFilePathesRecursively(string dir, vector<string>& filepathes, string extension = "*.*");

		// Func:
		//	Traverse sub directory name in speciald directory.
		// Input:
		//	dir				: specialed directory
		// Output:
		//	subdirnames		: sub directory name vector
		void TraverseSubDirectoryNames(string dir, vector<string>& subdirnames);

		// Func:
		//	Traverse sub directory path in speciald directory.
		// Input:
		//	dir				: specialed directory
		// Output:
		//	subdirpathes	: sub directory path vector
		void TraverseSubDirectoryPathes(string dir, vector<string>& subdirpathes);

		// Func:
		//	Normalize path, that is, convert path format to unix/linux mode.
		// Input:
		//	input_path		: intput path(any format)
		// Output:
		//	output_path		: output path(unix/linux format)
		void NormalizePath(string input_path, string& output_path);

		// Func:
		//	Check if it is a directory.
		// Input:
		//	input_path	: input path
		// Return:
		//	bool		: true or false
		bool IsDirectory(string input_path);

		// Func:
		//	Check if it is a file.
		// Input:
		//	input_path	: input path
		// Return:
		//	bool		: true or false
		bool IsFile(string input_path);

		// Func:
		//	Check if exist.
		// Input:
		//	input_path	: input path
		// Return:
		//	bool		: true or false
		bool Exist(string input_path);

		// Func:
		//	Get file size.
		// Input:
		//	filepath	: file path
		// Return:
		//	long long	: file size
		long long GetFileSizeX(string filepath);

		// Func:
		//	Get file name from fullpath.
		// Input:
		//	filepath	: file path
		// Return:
		//	string		: file name 
		string GetFileName(string filepath);

		// Func:
		//	Get file extension from fullpath.
		// Input:
		//	filepath	: file path
		// Return:
		//	string		: file extension 
		string GetFileExtension(string filepath);

		// Func:
		//	Get file name from fullpath without extension.
		// Input:
		//	filepath	: file path
		// Return:
		//	string		: file name without extension
		string GetFileNameWithoutExtension(string filepath);

		// Func:
		//	Get file path from fullpath without extension.
		// Input:
		//	filepath	: file path
		// Return:
		//	string		: file path without extension
		string GetFilePathWithoutExtension(string filepath);

		// Func:
		//	Get directory name from fullpath.
		// Input:
		//	dirpath		: file path
		// Return:
		//	string		: dir name 
		string GetFileDirectoryName(string filepath);

		// Func:
		//	Get dir name from fullpath.
		// Input:
		//	dirpath		: dir path
		// Return:
		//	string		: dir name 
		string GetDirectoryName(string dirpath);

	private:

		// Func:
		//	Traverse name/path in specialed directory.
		// Input:
		//	dir			: specialed directory
		//	extension	: extension, e.g. *.*, *.jpg
		//	type		: 0: get name, 1: get path, 2: get subdir name, 3: get subdir path
		//	recursive	: true: recursive, false: no-recursive
		// Output:
		//	filenames	: file name vector
		void Traverse(string dir, vector<string>& filenames, string extension, int type, bool recursive);

	};
}


#endif // __VRAUX_FILESYSTEM_H__