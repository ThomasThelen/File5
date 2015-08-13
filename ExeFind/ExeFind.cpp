// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
#include <vector>
#include <atlbase.h>
#include <stdio.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <errno.h>

using namespace std;

int ComputeMd5(vector<string> file_list, FILE* data_file);

vector<string> FindFiles()
{
	WIN32_FIND_DATA file_data; // A structure of information about the file.
	vector<string> exe_list; // A container for the list of exe files.
	string home_directory; // Holds the path for the home directory
	string current_directory;
	string directory;
	string filestring; // Holds the filename in a string for manipulation 
	vector<string> directories;
	string filepath;
	HANDLE searcher_handle = NULL;
	string first_directory = home_directory;
	DWORD binary_type;
	vector<string> empty;
	FILE *data_handle;

	// Get the system directory
	home_directory = getenv("SYSTEMDRIVE"); // Get the drive letter
	if (home_directory == "NULL") // Check for failure
	{
		MessageBoxA(NULL, "Failed to get home directoy", "Error", MB_OK);
		return empty;
	}
	cout << "Home Directory: " + home_directory << endl << endl; // Verify results
	filestring = file_data.cFileName;
	directories.push_back(first_directory);
	int j = 0, k = 0;

	for (int i = 0; i <= j; i++)
	{
		current_directory = directories[i];
		current_directory.append("\\*");
		cout << "Current directory: " << current_directory << endl;
		searcher_handle = FindFirstFile(current_directory.c_str(), &file_data); // Set the searcher to the first file in the directory and load the file's information to the file_data structure
		if (searcher_handle == INVALID_HANDLE_VALUE && GetLastError() != 5)
		{
			cout << GetLastError() << endl;
			MessageBoxA(NULL, "" + GetLastError(), "Error", MB_OK);
			FindClose(searcher_handle);
			return empty;
		}


		// Iterate through a directory
		current_directory.pop_back();
		while (FindNextFile(searcher_handle, &file_data))
		{
			filestring = file_data.cFileName;
			filepath = current_directory + filestring;
			directory = current_directory + filestring;
			GetBinaryType(filepath.c_str(), &binary_type);

			if (file_data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				directories.push_back(directory);
				//cout << "Directory: " << directories[j] << endl;
				j = j + 1;
			}

			if (filestring.find(".exe") != string::npos)
			{
				exe_list.push_back(filepath); // Put the exe name in the exe_list container
				k = k + 1;
				if (k > 10)
				{
					ComputeMd5(exe_list, data_handle);
					exe_list.clear();
					k = 0;
				}
			}
		}

	}
	FindClose(searcher_handle);
	cout << endl << "========" << endl;
	cout << "Finished Locating Files" << endl;
	return exe_list; // Return the vector with the list of exe files
}

int ComputeMd5(vector<string> file_list, FILE* data_file)
{
	FILE *file;
	MD5_CTX  md5_hash;
	vector<string>::iterator file_iterator;
	unsigned int file_bytes;
	unsigned char file_buffer[100000];
	unsigned char digest[16];

	for (unsigned int i = 0; i < file_list.size(); i++)
	{
	Top:
		file = fopen(file_list[i].c_str(), "rb");
		if (file == NULL)
		{
			file_list.erase(file_list.begin());
			goto Top;
		}
		MD5_Init(&md5_hash);

		while (!feof(file))
		{
			file_bytes = fread(file_buffer, sizeof(unsigned char), 16384, file);
			MD5_Update(&md5_hash, file_buffer, file_bytes);
		}
		MD5_Final(digest, &md5_hash);
		for (int m = 0; m < 16; m++)
		{
			//write to file
			fprintf(data_file, "%02x", digest[m]);
		}
		cout << file_list[i] << endl;
		fprintf(data_file, "%s", file_list[i].c_str());
		fprintf(data_file, "\n");
		memset(&digest, 0, sizeof(digest));
		fclose(file);
	}
	file_list.clear();
	return 0;
}

int main()
{
	vector<string> filenames;
	filenames = FindFiles(); // Search and return all .exe files on the system in a vector
	return 0;
}