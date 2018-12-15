#include "EasyLame.h"

using namespace MediaFramework;

EasyLame::EasyLame() : 
    lameUtility(lame_init())
{
 
}

EasyLame::~EasyLame()
{
    lame_close(lameUtility);
}

void EasyLame::Close()
{
    lame_close(lameUtility);
}

int EasyLame::SetSampleRate(int sampleRate)
{
    return lame_set_in_samplerate(lameUtility, sampleRate);
}

int EasyLame::SetByteRate(int byteRate)
{
    return lame_set_brate(lameUtility, byteRate);
}

int EasyLame::SetNumberOfChannels(int channels)
{
    return lame_set_num_channels(lameUtility, channels);
}

int EasyLame::SetMode(MPEG_mode_e mode)
{
    return lame_set_mode(lameUtility, mode);
}

int EasyLame::SetDecodeOnly(int decodeOnly)
{
    return lame_set_decode_only(lameUtility, decodeOnly);
}

int EasyLame::SetVBR(vbr_mode_e VBRMode)
{
    return lame_set_VBR(lameUtility, VBRMode);
}


/* initialize the encoder and sets more internal configuration based on data provided.
 * returns -1 if something failed.
 */
int EasyLame::Init()
{
    return lame_init_params(lameUtility);
}

/*
 * REQUIRED:
 * lame_encode_flush will flush the intenal PCM buffers, padding with
 * 0's to make sure the final frame is complete, and then flush
 * the internal MP3 buffers, and thus may return a
 * final few mp3 frames.  'mp3buf' should be at least 7200 bytes long
 * to hold all possible emitted data.
 *
 * will also write id3v1 tags (if any) into the bitstream
 *
 * return code = number of bytes output to mp3buf. Can be 0
 */
int EasyLame::EncodeFlush(unsigned char * mp3Buffer, int size)
{
    return lame_encode_flush(lameUtility, mp3Buffer, size);
}

/*
 * input pcm data, output (maybe) mp3 frames.
 * This routine handles all buffering, resampling and filtering for you.
 *
 * return code     number of bytes output in mp3buf. Can be 0
 *                 -1:  mp3buf was too small
 *                 -2:  malloc() problem
 *                 -3:  lame_init_params() not called
 *                 -4:  psycho acoustic problems
 *
 * The required mp3buf_size can be computed from num_samples,
 * samplerate and encoding rate, but here is a worst case estimate:
 *
 * mp3buf_size in bytes = 1.25*num_samples + 7200
 *
 * I think a tighter bound could be:  (mt, March 2000)
 * MPEG1:
 *    num_samples*(bitrate/8)/samplerate + 4*1152*(bitrate/8)/samplerate + 512
 * MPEG2:
 *    num_samples*(bitrate/8)/samplerate + 4*576*(bitrate/8)/samplerate + 256
 *
 * but test first if you use that!
 *
 * set mp3buf_size = 0 and LAME will not check if mp3buf_size is
 * large enough.
 *
 * NOTE:
 * if gfp->num_channels=2, but gfp->mode = 3 (mono), the L & R channels
 * will be averaged into the L channel before encoding only the L channel
 * This will overwrite the data in buffer_l[] and buffer_r[].
 *
*/
int EasyLame::EncodeBuffer(const short int bufferLeftChannel [], 
					       const short int bufferRightChannel [],
                           const int nSamples, unsigned char* mp3Buffer,
                           const int mp3BufferSize )
{
    return lame_encode_buffer(lameUtility, bufferLeftChannel, bufferRightChannel, nSamples, mp3Buffer, mp3BufferSize);
}
	
/*
 * as above, but input has L & R channel data interleaved.
 * NOTE:
 * num_samples = number of samples in the L (or R)
 * channel, not the total number of samples in pcm[]
 */
int EasyLame::EncodeInterleaved(short int pcm[], int nSamples, unsigned char* mp3Buffer, int mp3BufferSize)
{
    return lame_encode_buffer_interleaved(lameUtility, pcm, nSamples, mp3Buffer, mp3BufferSize);
}

