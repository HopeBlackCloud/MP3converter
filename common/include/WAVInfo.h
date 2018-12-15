/****************************************************************
 This class aims to hold the information of the given .wav file. 


 Author: Murat Karabulut
 Date:   06.06.2018
*****************************************************************/
#ifndef WAVINFO_H
#define WAVINFO_H

#include <string>
#include <vector>       

#include "Definitions.h"
#include "WavFileException.h"  

#ifdef _WINDOWS
#pragma warning(disable : 4290)
#endif

using namespace std;

namespace MediaFramework
{
	class WAVInfo
	{
		public:
			WAVInfo();
			virtual ~WAVInfo();

			void ReadWavFile(const string & filename) throw (WavFileException);

			int16_t GetChannels() const;
			int32_t GetSamplesPerSec() const;
			int32_t GetAvgBytesPerSec() const;
			int32_t GetDataSize() const;

		private:
			vector<BYTE>   wave;

			WAVRiff         wavRiff;
			WAVFormatHeader wavFormatHeader;
			WAVFormat       wavFormat;
			WAVFact         wavFact;
			WAVData         wavData;

			int16_t      extraParamLength;
			vector<BYTE> extraParam;
			vector<BYTE> formatExtraBytes;
	};
}

#endif
