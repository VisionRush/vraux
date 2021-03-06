﻿#include "vraux/vraux_filesystem.h"

namespace visionrush
{
	// -----------------------------------------------------------------------------------
	// Public
	// -----------------------------------------------------------------------------------

	void VRFileSystemTool::TraverseFileNames(string dir, vector<string>& filenames, string extension)
	{
		Traverse(dir, filenames, extension, 0, false);
	}

	void VRFileSystemTool::TraverseFileNamesRecursively(string dir, vector<string>& filenames, string extension)
	{
		Traverse(dir, filenames, extension, 0, true);
	}

	void VRFileSystemTool::TraverseFilePathes(string dir, vector<string>& filepathes, string extension)
	{
		Traverse(dir, filepathes, extension, 1, false);
	}

	void VRFileSystemTool::TraverseFilePathesRecursively(string dir, vector<string>& filepathes, string extension)
	{
		Traverse(dir, filepathes, extension, 1, true);
	}

	void VRFileSystemTool::TraverseSubDirectoryNames(string dir, vector<string>& subdirpathes)
	{
		Traverse(dir, subdirpathes, "*.*", 2, false);
	}

	void VRFileSystemTool::TraverseSubDirectoryPathes(string dir, vector<string>& subdirpathes)
	{
		Traverse(dir, subdirpathes, "*.*", 3, false);
	}

	void VRFileSystemTool::TraverseSubDirectoryPathesRecursively(string dir, vector<string>& subdirpathes)
	{
		Traverse(dir, subdirpathes, "*.*", 3, true);
	}

	void VRFileSystemTool::NormalizePath(string input_path, string& output_path)
	{
		// convert path format to unix/linux mode.
		output_path = input_path;
		string::size_type pos = 0;
		while ((pos = output_path.find("\\", pos)) != string::npos)
		{
			output_path.replace(pos, 1, "/");
			pos += 1;
		}
		pos = 0;
		while ((pos = output_path.find("//", pos)) != string::npos)
		{
			output_path.replace(pos, 2, "/");
			pos += 1;
		}
		// supplement directory path
#if defined Q_OS_WIN
		if (_access(input_path.c_str(), 0) != -1 && GetFileAttributes(input_path.c_str()) & FILE_ATTRIBUTE_DIRECTORY)
			if (output_path.back() != '/') output_path += "/";
#elif defined Q_OS_LINUX
		struct stat filestat;
		lstat(input_path.c_str(), &filestat);
		if (access(input_path.c_str(), 0) != -1 && S_ISDIR(filestat.st_mode))
			if (output_path.back() != '/') output_path += "/";
#else
#endif
	}


	bool VRFileSystemTool::IsDirectory(string input_path)
	{
#if defined Q_OS_WIN
		if (_access(input_path.c_str(), 0) == -1)
			return false;
		if (GetFileAttributes(input_path.c_str()) & FILE_ATTRIBUTE_DIRECTORY)
			return true;
		else return false;
#elif defined Q_OS_LINUX
		if (access(input_path.c_str(), 0) == -1)
			return false;
		struct stat filestat;
		lstat(input_path.c_str(), &filestat);
		if (S_ISDIR(filestat.st_mode))
			return true;
		else return false;
#else
#endif
	}

	bool VRFileSystemTool::IsFile(string input_path)
	{
#if defined Q_OS_WIN
		if (_access(input_path.c_str(), 0) == -1)
			return false;
		if (GetFileAttributes(input_path.c_str()) & FILE_ATTRIBUTE_ARCHIVE)
			return true;
		else return false;
#elif defined Q_OS_LINUX
		if (access(input_path.c_str(), 0) == -1)
			return false;
		struct stat filestat;
		lstat(input_path.c_str(), &filestat);
		if (S_ISREG(filestat.st_mode))
			return true;
		else return false;
#else
#endif
	}

	bool VRFileSystemTool::Exist(string input_path)
	{
#if defined Q_OS_WIN
		if (_access(input_path.c_str(), 0) != -1)
			return true;
		else return false;
#elif defined Q_OS_LINUX
		if (access(input_path.c_str(), 0) != -1)
			return true;
		else return false;
#else
#endif
	}

	long long VRFileSystemTool::GetFileSizeX(string filepath)
	{
		// check 
		if (!IsFile(filepath)) return -1;

		long long filesize = 0;
#if defined Q_OS_WIN
		FILE* filehandler = fopen(filepath.c_str(), "rb");
		if (!filehandler) filesize = -1;
		else filesize = _filelengthi64(_fileno(filehandler));
		fclose(filehandler);

		//HANDLE handle = CreateFile(filepath.c_str(), FILE_READ_EA, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		//if (handle != INVALID_HANDLE_VALUE) filesize = GetFileSize(handle, NULL);
		//else filesize = -1;
		//CloseHandle(handle);
#elif defined Q_OS_LINUX
		struct stat filestat;
		if (lstat(filepath.c_str(), &filestat) < 0) filesize = -1;
		else filesize = filestat.st_size;
#else
#endif
		return filesize;
	}

	string VRFileSystemTool::GetFileName(string filepath)
	{
		// check 
		if (!IsFile(filepath)) return "";
		// normalize path
		NormalizePath(filepath, filepath);
		// location
		int pos1 = filepath.find_last_of('/');
		int pos2 = filepath.length();
		// return
		return  filepath.substr(pos1 + 1, (pos2 - pos1 - 1));
	}

	string VRFileSystemTool::GetFileExtension(string filepath)
	{
		// check 
		if (!IsFile(filepath)) return "";
		// normalize path
		NormalizePath(filepath, filepath);
		int pos1 = filepath.find_last_of('.');
		int pos2 = filepath.length() - 1;
		// check 
		if (pos1 == -1) return "";
		string s = "";
		s = filepath.substr(pos1, (pos2 - pos1 + 1));
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		return s;
	}

	string VRFileSystemTool::GetFileNameWithoutExtension(string filepath)
	{
		// check 
		if (!IsFile(filepath)) return "";
		// normalize path
		NormalizePath(filepath, filepath);
		// location
		int pos1 = filepath.find_last_of('/');
		int pos2 = filepath.find_last_of('.');
		// check
		if (pos2 == -1) pos2 = filepath.length();
		// return
		return  filepath.substr(pos1 + 1, (pos2 - pos1 - 1));
	}

	string VRFileSystemTool::GetFilePathWithoutExtension(string filepath)
	{
		// check 
		if (!IsFile(filepath)) return "";
		// normalize path
		NormalizePath(filepath, filepath);
		// location
		int pos1 = 0;
		int pos2 = filepath.find_last_of('.');
		// check
		if (pos2 == -1) pos2 = filepath.length();
		// return
		return  filepath.substr(pos1, (pos2 - pos1));
	}

	string VRFileSystemTool::GetFileDirectoryName(string filepath)
	{
		// check 
		if (!IsFile(filepath)) return "";
		// normalize path
		NormalizePath(filepath, filepath);
		// location
		int pos1 = filepath.find_last_of('/');
		int pos2 = filepath.find_last_of('/', pos1 - 1);
		// check
		if (pos2 == -1 || pos1 == pos2) return "";
		// return
		return  filepath.substr(pos2 + 1, (pos1 - pos2 - 1));
	}

	string VRFileSystemTool::GetDirectoryName(string dirpath)
	{
		// check 
		if (!IsDirectory(dirpath)) return "";
		// normalize path
		NormalizePath(dirpath, dirpath);
		// location
		int pos1 = dirpath.find_last_of('/');
		int pos2 = dirpath.find_last_of('/', pos1 - 1);
		// check
		if (pos2 == -1 || pos1 == pos2) return "";
		// return
		return  dirpath.substr(pos2 + 1, (pos1 - pos2 - 1));
	}

	string VRFileSystemTool::GetPWD()
	{
		string dirpath;
		// get pwd
		char buffer[1024];
		getcwd(buffer, 1024);
		// return
		dirpath = buffer;
		NormalizePath(dirpath, dirpath);
		return dirpath;
	}

	int VRFileSystemTool::CreateDirectoryx(string dirpath)
	{
#if defined Q_OS_WIN
		return mkdir(dirpath.c_str());
#elif defined Q_OS_LINUX
		return mkdir(dirpath.c_str(), S_IRWXU);
#else
#endif
	}


	int VRFileSystemTool::ReadLineFromTxt(string filepath, vector<string>& lines)
	{
		// open text file
		ifstream ifs(filepath);
		if (!ifs.is_open())
		{
			printf("libvr-err: failed to open file!.\n");
			return -1;
		}
		// read line
		string line;
		while (getline(ifs, line))
		{
#if defined Q_OS_LINUX
			if (line[line.length() - 1] == '\r')	// only linux
				line = line.substr(0, line.length() - 1);
#endif
			if (line.empty()) continue;
			//printf("%s\n", line.c_str());
			lines.push_back(line);
	}
		ifs.close();
		// return
		return lines.size();
}


	int VRFileSystemTool::RemoveDirectoryx(string dirpath)
	{
		// check
		if (!IsDirectory(dirpath)) return 1;
		// remove
		int state = rmdir(dirpath.c_str());
#if defined Q_OS_WIN
		if (state != 0)
		{
			int errcode = GetLastError();
			char errmsg[512];
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errcode, 0, errmsg, sizeof(errmsg), NULL);
			printf("libvr-err: errcode is %3d, errmsg is %s", errcode, errmsg);
		}
#elif defined Q_OS_LINUX
#else
#endif
		return state;
		}


	int VRFileSystemTool::CopyFilex(string src_path, string dst_path, bool bfailifexists)
	{
		// check
		if (!Exist(src_path)) return 1;
		// copy
#if defined Q_OS_WIN
		int state = !CopyFile(src_path.c_str(), dst_path.c_str(), bfailifexists);
		if (state != 0)
		{
			int errcode = GetLastError();
			char errmsg[512];
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errcode, 0, errmsg, sizeof(errmsg), NULL);
			printf("libvr-err: errcode is %3d, errmsg is %s", errcode, errmsg);
		}
		return state;
#elif defined Q_OS_LINUX
		FILE *fp1;
		fp1 = fopen(src_path.c_str(), "r");
		FILE *fp2;
		fp2 = fopen(dst_path.c_str(), "w");
		char buff[200] = {'\0'};
		while (fgets(buff, sizeof(buff), fp1) != NULL)
		{
			fputs(buff, fp2);
		}
		fclose(fp1);
		fclose(fp2);
		return 0;
#else
#endif
	}

	int VRFileSystemTool::MoveFilex(string src_path, string dst_path)
	{
		// check
		if (!Exist(src_path)) return 1;
		// move
		int state = rename(src_path.c_str(), dst_path.c_str());
#if defined Q_OS_WIN
		if (state != 0)
		{
			int errcode = GetLastError();
			char errmsg[512];
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errcode, 0, errmsg, sizeof(errmsg), NULL);
			printf("libvr-err: errcode is %3d, errmsg is %s", errcode, errmsg);
		}
#elif defined Q_OS_LINUX
#else
#endif
		return state;
		}

	int VRFileSystemTool::RemoveFile(string filepath)
	{
		// check 
		if (!IsFile(filepath)) return -1;
		// remove
		int state = remove(filepath.c_str());
#if defined Q_OS_WIN
		if (state != 0)
		{
			int errcode = GetLastError();
			char errmsg[512];
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errcode, 0, errmsg, sizeof(errmsg), NULL);
			printf("libvr-err: errcode is %3d, errmsg is %s", errcode, errmsg);
		}
#elif defined Q_OS_LINUX
#else
#endif
		return state;
		}

	// -----------------------------------------------------------------------------------
	// Private
	// -----------------------------------------------------------------------------------

#if defined Q_OS_WIN
	void VRFileSystemTool::Traverse(string dir, vector<string>& filenames, string extension, int type, bool recursive)
	{
		// normalize path
		string normdir;
		NormalizePath(dir, normdir);
		// check dir validity
		if (_access(normdir.c_str(), 0) == -1)
		{
			printf("libvr: dir not exist!.\n");
			return;
		}
		// create search template
		string file_searchtemplate;
		file_searchtemplate = normdir + extension;
		// find file
		struct _finddata_t fileinfo;
		intptr_t filehandle;
		if ((filehandle = _findfirst(file_searchtemplate.c_str(), &fileinfo)) != -1l)
		{
			do
			{
				if (strcmp(".", fileinfo.name) == 0 || strcmp("..", fileinfo.name) == 0)
					continue;
				switch (type)
				{
				case 0:	// "name"
					if (fileinfo.attrib == _A_ARCH)
						filenames.push_back(fileinfo.name);
					break;
				case 1:	// "path"
					if (fileinfo.attrib == _A_ARCH)
						filenames.push_back(normdir + fileinfo.name);
					break;
				case 2:	// "subdir name"
					if (fileinfo.attrib == _A_SUBDIR)
						filenames.push_back(fileinfo.name);
					break;
				case 3:	// "subdir path"
					if (fileinfo.attrib == _A_SUBDIR)
						filenames.push_back(normdir + fileinfo.name);
					break;
				}
			} while (_findnext(filehandle, &fileinfo) == 0);
		}
		// check recursive
		if (recursive)
		{
			// create search template
			string dir_searchtemplate;
			dir_searchtemplate = normdir + "*.*";
			// find sub directory
			if ((filehandle = _findfirst(dir_searchtemplate.c_str(), &fileinfo)) != -1l)
			{
				do
				{
					if (strcmp(".", fileinfo.name) == 0 || strcmp("..", fileinfo.name) == 0)
						continue;
					if (fileinfo.attrib == _A_SUBDIR)
						Traverse(normdir + fileinfo.name, filenames, extension, type, recursive);
				} while (_findnext(filehandle, &fileinfo) == 0);
			}
		}
		_findclose(filehandle);
	}
#elif defined Q_OS_LINUX
	void VRFileSystemTool::Traverse(string dir, vector<string>& filenames, string extension, int type, bool recursive)
	{
		// normalize path
		string normdir;
		NormalizePath(dir, normdir);
		// check dir validity
		if (access(normdir.c_str(), 0) == -1)
		{
			printf("libvr: dir not exist!.\n");
			return;
		}
		// find file
		DIR * filehandle;
		struct stat filestat;
		struct dirent *fileinfo;
		if ((filehandle = opendir(normdir.c_str())) != NULL)
		{
			while ((fileinfo = readdir(filehandle)) != NULL)
			{
				if (strcmp(".", fileinfo->d_name) == 0 || strcmp("..", fileinfo->d_name) == 0)
					continue;
				string filepath = normdir + fileinfo->d_name;
				string filename = fileinfo->d_name;
				string extension_s = extension.substr(1, extension.length());
				lstat(filepath.c_str(), &filestat);
				switch (type)
				{
				case 0:	// "name"
					if (S_ISREG(filestat.st_mode))
						if (strcmp("*.*", extension.c_str()) == 0 || (filename.length() - int(filename.find(extension_s.c_str())) - extension_s.length()) == 0)
							filenames.push_back(filename);
					break;
				case 1:	// "path"
					if (S_ISREG(filestat.st_mode))
						if (strcmp("*.*", extension.c_str()) == 0 || (filename.length() - int(filename.find(extension_s.c_str())) - extension_s.length()) == 0)
							filenames.push_back(filepath);
					break;
				case 2:	// "subdir name"
					if (S_ISDIR(filestat.st_mode))
						filenames.push_back(filename);
					break;
				case 3:	// "subdir path"
					if (S_ISDIR(filestat.st_mode))
						filenames.push_back(filepath);
					break;
				}
			}
		}
		// check recursive
		if (recursive)
		{
			// find sub directory
			if ((filehandle = opendir(normdir.c_str())) != NULL)
			{
				while ((fileinfo = readdir(filehandle)) != NULL)
				{
					if (strcmp(".", fileinfo->d_name) == 0 || strcmp("..", fileinfo->d_name) == 0)
						continue;
					string subdir = normdir + fileinfo->d_name;
					lstat(subdir.c_str(), &filestat);
					if (S_ISDIR(filestat.st_mode))
						Traverse(subdir.c_str(), filenames, extension, type, recursive);
				}
			}
		}
	}
#else

#endif

	}

