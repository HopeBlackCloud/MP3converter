/****************************************************************
 This class is derived from WorkerThread class and aimst to
 implement Run method so it has its own execution.

 For encoding process, each thread is responsible for encoding a 
 .wav file to MP3 format.
 Each thread reads .wav file, encode it to MP3 and than
 save this file to the destination folder.

 Author: Murat Karabulut
 Date:   06.06.2018
*****************************************************************/
#ifndef ENCODER_THREAD_H
#define ENCODER_THREAD_H

#include <string>
#include "WorkerThread.h"

using namespace std;

namespace MediaFramework
{
	class EncoderThread : public WorkerThread
	{
		public:
			EncoderThread(const string& wavFile);
			~EncoderThread(void);

			void Run();

			inline bool isEncodingFinished() const { return isFinished; }

		private:
			string wavFilePath;
			string mp3FilePath;
			bool isFinished;
	};
}
#endif

