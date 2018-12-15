/****************************************************************
 This file includes all required definitons for classes.

 Author: Murat Karabulut
 Date:   06.06.2018
*****************************************************************/
#ifndef DEF_H
#define DEF_H

#include <stdint.h> 

namespace MediaFramework
{
	typedef char BYTE;

	const int NUMBER_OF_THREADS_PER_CORE = 2;
	const int WAIT_DURATION_IN_MS = 100;

	const int RIFF_SIZE = 12;
	const int FORMAT_HEADER_SIZE = 8;
	const int FORMAT_SIZE = 16;
	const int DATA_SIZE   = 8;
	const int FACT_SIZE   = 8;

	const int PCM_SIZE = 8192;
	const int MP3_SIZE = 8192;

	struct WAVRiff
	{
		BYTE riffID[4];   
		int32_t riffSIZE;   
		BYTE riffFORMAT[4]; 
	};

	struct WAVFormatHeader
	{
		BYTE fmtID[4];     
		int32_t fmtSIZE;    
	};

	struct WAVFormat
	{
		int16_t wFormatTag; 
		int16_t nChannels;  
		int32_t nSamplesPerSec;     
		int32_t nAvgBytesPerSec;    
		int16_t nBlockAlign;      
		int16_t wBitsPerSample;     
	};

	struct WAVData
	{
		BYTE dataID[4];     
		int32_t dataSIZE;   
	};

	struct WAVFact
	{
		int32_t samplesNumber;
		int32_t t;
	};
}
#endif
