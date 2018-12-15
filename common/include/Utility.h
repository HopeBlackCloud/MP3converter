/****************************************************************
 This class aims to serve O.S operations and utilities for other
 classes. This class is a static class, all method can be invoked
 without creating instance of this class.

 Author: Murat Karabulut
 Date:   06.06.2018
*****************************************************************/
#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

using namespace std;

namespace MediaFramework
{
	class Utility
	{
		public:
			static void GetFilesInFolder(const string &directoryPath,
										 vector<string> &wavFilesToBeFilled);

			static bool IsWAVFile(const string& fileName);
			static string PrepareMP3FileName(const string &wavFilePath);
			static int GetNumberOfCPUCores();
			static void Encode(const string& wavFile, const string& mp3FileName);

		private:
			Utility(void) { }
	};
}


#endif

