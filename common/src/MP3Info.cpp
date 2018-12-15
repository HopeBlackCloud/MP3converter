#include "MP3Info.h"
#include <cstring>  

using namespace MediaFramework; 

MP3Info::MP3Info()
{
    std::memset(&mp3Info, 0, sizeof(mp3Info));
}

bool MP3Info::IsHeaderParsed() const
{
    return mp3Info.header_parsed == 1;
}

int MP3Info::GetNumberOfChannels() const
{
    return mp3Info.stereo;
}

int MP3Info::GetSampleRate() const
{
    return mp3Info.samplerate;
}

int MP3Info::GetBitRate() const
{
    return mp3Info.bitrate;
}