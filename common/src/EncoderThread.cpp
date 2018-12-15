#include "EncoderThread.h"

#include "Utility.h"

using namespace std;

using namespace MediaFramework;

EncoderThread::EncoderThread(const string& wavFile) :
    wavFilePath(wavFile),
    mp3FilePath(Utility::PrepareMP3FileName(wavFilePath)),
    isFinished(false)
{

}

EncoderThread::~EncoderThread(void)
{

}

void EncoderThread::Run()
{
	Utility::Encode(wavFilePath, mp3FilePath);
	isFinished = true;
}
