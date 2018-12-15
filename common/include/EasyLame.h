/****************************************************************
 This class is just a wrapper class for lame. All lame related
 methods should be called via this class.

 Author: Murat Karabulut
 Date:   06.06.2018
*****************************************************************/
#ifndef EASY_LAME_H
#define EASY_LAME_H

#include <lame.h>

namespace MediaFramework
{
	class EasyLame
	{
		public:
			EasyLame();
			~EasyLame();

			int SetSampleRate(int sampleRate);
			int SetByteRate(int byteRate);

			int SetNumberOfChannels(int channels);
			int SetMode(MPEG_mode_e mode);

			int SetDecodeOnly(int decodeOnly);

			int SetVBR(vbr_mode_e VBRMode);
			int Init();
			void Close();
			int EncodeFlush(unsigned char * mp3Buffer, int size);

			int EncodeBuffer(const short int bufferLeftChannel [], 
							 const short int bufferRightChannel [],
							 const int nSamples, unsigned char* mp3Buffer,
							 const int mp3BufferSize);
												 
			int EncodeInterleaved(short int pcm[], int nSamples, 
								  unsigned char* mp3Buffer, int mp3BufferSize);
													  
		private:
			lame_t lameUtility;
	};
}

#endif

