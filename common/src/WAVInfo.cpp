#include "WAVInfo.h"     
    
#include <fstream>                 
#include <cstring>         

using namespace MediaFramework;

WAVInfo::WAVInfo() : extraParamLength(0)
{
    wavFormat.wFormatTag  = 0;
    wavFact.samplesNumber = -1;
}

WAVInfo::~WAVInfo()
{

}

void WAVInfo::ReadWavFile(const string & filename) throw (WavFileException)
{
    // open .wav file in binary mode, if it fails throw exception
    ifstream file(filename.c_str(), ios_base::binary | ios_base::in);
    if (!file.is_open())
    {
        throw WavFileException();
    }

    file.read(reinterpret_cast<BYTE*>(&wavRiff), RIFF_SIZE);
    file.read(reinterpret_cast<BYTE*>(&wavFormatHeader), FORMAT_HEADER_SIZE);
    file.read(reinterpret_cast<BYTE*>(&wavFormat), FORMAT_SIZE);

    unsigned fmtExtraBytes = wavFormatHeader.fmtSIZE - FORMAT_SIZE;

    if (fmtExtraBytes > 0)
    {
        formatExtraBytes.resize(fmtExtraBytes);

        file.read(&formatExtraBytes[0], fmtExtraBytes);
    }

    if (wavFormat.wFormatTag != 1)
    {
        file.read(reinterpret_cast<BYTE*>(&extraParamLength), 2); 
        if (extraParamLength > 0)
        {
            extraParam.resize(extraParamLength);
            file.read(&extraParam[0], extraParamLength);
        }
    }

    file.read(reinterpret_cast<BYTE*>(&wavData.dataID), 4);

    if( wavData.dataID[0] == 'f' && wavData.dataID[1] == 'a' && 
		wavData.dataID[2] == 'c' && wavData.dataID[3] == 't' )
    {
        file.read(reinterpret_cast<BYTE*>(&wavFact), FACT_SIZE);
        file.read(reinterpret_cast<BYTE*>(&wavData), DATA_SIZE);
    }
    else
        file.read( reinterpret_cast<BYTE*>(&wavData.dataSIZE), 4);

    wave.resize(wavData.dataSIZE);

    file.read(&wave[0], wavData.dataSIZE);
}

int16_t WAVInfo::GetChannels() const
{
    return wavFormat.nChannels;
}

int32_t WAVInfo::GetSamplesPerSec() const
{
    return wavFormat.nSamplesPerSec;
}

int32_t WAVInfo::GetAvgBytesPerSec() const
{
    return wavFormat.nAvgBytesPerSec;
}

int32_t WAVInfo::GetDataSize() const
{
    return wavData.dataSIZE;
}
