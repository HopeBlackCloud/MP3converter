/****************************************************************
 This class aims to create and manage threads to accomplish the job.


 Author: Murat Karabulut
 Date:   06.06.2018
*****************************************************************/
#ifndef ENCODER_CONTROLLER_H
#define ENCODER_CONTROLLER_H

#include "EncoderThread.h"

#include <vector>
#include <string>

using namespace std;

namespace MediaFramework
{
	class EncoderController
	{
		public:
			EncoderController(const string& dirName);
			~EncoderController(void);

			void StartEncoders();
			void Cleanup();

		private:
			string directoryPath;
			vector<EncoderThread *> encoderThreads;
			size_t maxThreadLimit;
	};
}

#endif
