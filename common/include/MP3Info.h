/****************************************************************
This class aims to hold the information of .mp3 file. 

 Author: Murat Karabulut
 Date:   06.06.2018
*****************************************************************/
#ifndef MP3INFO_H
#define MP3INFO_H

#include <lame.h>

namespace MediaFramework
{
	class MP3Info
	{
		public:
			MP3Info();

			int GetBitRate() const;
			int GetSampleRate() const;
			int GetNumberOfChannels() const;
			bool IsHeaderParsed() const;

		private:
			mp3data_struct mp3Info;
	};
}

#endif

