#include "EncoderController.h"

#include "Utility.h"
#include "Definitions.h"

#include <iostream>

#ifdef _WINDOWS
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace MediaFramework;

EncoderController::EncoderController(const string& dirPath):
    directoryPath(dirPath),
    maxThreadLimit(Utility::GetNumberOfCPUCores() * NUMBER_OF_THREADS_PER_CORE)
{
	// get number of cores from OS. Each core is assumed to have 2 threads by default. 
}

EncoderController::~EncoderController(void)
{

}

void EncoderController::StartEncoders()
{
	vector<string> wavFilePaths;
	Utility::GetFilesInFolder(directoryPath, wavFilePaths);
	
	vector<EncoderThread*>::iterator it;

	// do for all wav files in the given directory
	for (size_t i = 0; i < wavFilePaths.size(); i++)
	{
		// check whether thread limit exceeded, if so wait thread until it is available 
		while(encoderThreads.size() >= maxThreadLimit)
		{
			// wait 100ms thus busy threads can complete their jobs.
			#ifdef _WINDOWS
				Sleep(WAIT_DURATION_IN_MS); 
			#else
				usleep(WAIT_DURATION_IN_MS * 1000);
			#endif			

			// check all the busy threads, if their jobs is completed, delete from thread list.
			for (it = encoderThreads.begin(); it != encoderThreads.end();)
			{
				if ((*it)->isEncodingFinished())
				{
					(*it)->WaitForThreadToExit();
					delete *it;  
					it = encoderThreads.erase(it);
				}
				else 
				{
					++it;
				}
			}
		}

		// waiting ends, which means available thread exists.
		// so create encoder thread and give wav file to be encoded.
		EncoderThread *encThread = new EncoderThread(wavFilePaths.at(i));
		if (encThread->StartThread())
		{
			encoderThreads.push_back(encThread);
			cout<<"Encoding "<<wavFilePaths.at(i)<<" file to MP3!"<<endl;
		}
		else
			cerr<<"Encoding could not start for "<<wavFilePaths.at(i)<<" file!"<<endl;
	}
}

void EncoderController::Cleanup()
{
	vector<EncoderThread*>::iterator it;
	for ( it = encoderThreads.begin(); it != encoderThreads.end();)
	{
		(*it)->WaitForThreadToExit();

		if ((*it)->isEncodingFinished())
		{
			delete *it;  
			it = encoderThreads.erase(it);
		}
		else 
		{
			++it;
		}
	}
}




