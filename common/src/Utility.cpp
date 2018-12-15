#include "Utility.h"

#include <stdio.h>
#include <iostream>  

#include "WAVInfo.h"
#include "EasyLame.h"

#ifdef _WINDOWS
    #include <windows.h>
#else
    #include <unistd.h>
    #include <dirent.h>
#endif

#define READ_BINARY_MODE  "rb"
#define WRITE_BINARY_MODE "wb"

const string MP3_FILE_EXTENSION  = ".mp3";
const string WAV_FILE_EXTENSION  = "wav";
const string WAVE_FILE_EXTENSION = "wave";
const string ALL_FILES_IN_DIR    = "\\*";

using namespace MediaFramework;

 void Utility::GetFilesInFolder(const string &directoryPath, vector<string> &wavFilesToBeFilled)
{
	#ifdef _WINDOWS	
		string allFilePath;
		allFilePath = directoryPath + ALL_FILES_IN_DIR;

		WIN32_FIND_DATA data;
		HANDLE hFind = FindFirstFile(LPCSTR(allFilePath.c_str()), &data);      

		if (hFind != INVALID_HANDLE_VALUE) 
		{
			do 
			{
			    if(IsWAVFile(data.cFileName))
				    wavFilesToBeFilled.push_back(directoryPath + string("/") + string(data.cFileName));

			} while (FindNextFile(hFind, &data));

			FindClose(hFind);
		}
		else
		{
			cerr<<"File read error in searching wav files in folder : "<<directoryPath<<endl;
		}
	#else
		DIR *dir;
		struct dirent *ent;
		if((dir = opendir(directoryPath.c_str())) != NULL)
		{
			while ((ent = readdir(dir)) != NULL)
			{
			   if(IsWAVFile(ent->d_name))
				    wavFilesToBeFilled.push_back(directoryPath + string("/") + string(ent->d_name));

			}
			closedir(dir);	
		}
		else
		{
			cerr<<"Directory read error in folder : "<<directoryPath<<endl;
		}
	#endif
}

bool Utility::IsWAVFile(const string& fileName)
{
	size_t found = fileName.find_last_of(".");
	if(fileName.substr(found+1, fileName.size()) == WAV_FILE_EXTENSION ||
	   fileName.substr(found+1, fileName.size()) == WAVE_FILE_EXTENSION)
		return true;
	else
		return false;
}

int Utility::GetNumberOfCPUCores()
{
    #ifdef _WINDOWS	
	    SYSTEM_INFO sysinfo;
	    GetSystemInfo(&sysinfo);
	    return sysinfo.dwNumberOfProcessors;
    #else
	    return sysconf(_SC_NPROCESSORS_ONLN);
    #endif
}

string Utility::PrepareMP3FileName(const string &wavFilePath)
{
	size_t found = wavFilePath.find_last_of(".");
	string mp3FilePath = wavFilePath.substr(0, found);
	mp3FilePath+=".mp3";

	return mp3FilePath;
}

void Utility::Encode(const string& wavFile, const string& mp3File)
{
	unsigned int sampleRate;
	unsigned int byteRate;
	unsigned int channels; 

	try
	{
		WAVInfo wav;
        wav.ReadWavFile(wavFile);

		sampleRate = wav.GetSamplesPerSec();
		byteRate   = wav.GetAvgBytesPerSec();
		channels   = wav.GetChannels(); 
	}
	catch (const WavFileException& exc)
	{
		cout<<wavFile <<" "<<exc.what()<<std::endl;
		return;
	}
	
	EasyLame lameService;

	int retCodeRead;
	int retCodeWrite;

    FILE *pcm = fopen(wavFile.c_str(), READ_BINARY_MODE);
    FILE *mp3 = fopen(mp3File.c_str(), WRITE_BINARY_MODE);

    short int pcmBuffer[PCM_SIZE * 2];
    unsigned char mp3Buffer[MP3_SIZE];

    lameService.SetSampleRate(sampleRate);
    lameService.SetByteRate(byteRate);

    if (channels == 1)
        lameService.SetMode(MONO);
 
    lameService.SetNumberOfChannels(channels);
    lameService.SetVBR(vbr_default);
	lameService.Init();

    do
	{
        retCodeRead = fread(pcmBuffer, 2 * sizeof(short int), PCM_SIZE, pcm);
        if (retCodeRead == 0)
			retCodeWrite = lameService.EncodeFlush(mp3Buffer, MP3_SIZE);
        else
			retCodeWrite = lameService.EncodeInterleaved(pcmBuffer, retCodeRead, mp3Buffer, MP3_SIZE);

        fwrite(mp3Buffer, retCodeWrite, 1, mp3);
    } 
	while (retCodeRead != 0);

	lameService.Close();
    fclose(mp3);
    fclose(pcm);
}
