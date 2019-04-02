#pragma once
extern "C"
{
#include <avcodec.h>
#include <avdevice.h>
#include <avfilter.h>
#include <avformat.h>
#include <avio.h>
#include <avutil.h>
#include <postprocess.h>
#include <swresample.h>
#include <swscale.h>
#include <frame.h>
#include <imgutils.h>
}


#include <SDL.h>
#include <SDL_thread.h>

#ifdef __MINGW32__
#undef main /* Prevents SDL from overriding main() */
#endif

#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <string>
#include <iostream>




#define SDL_MAIN_HANDLED
#define ERROR_SIZE 128
#define FORMATO AV_PIX_FMT_RGB24
#define SDL_AUDIO_BUFFER_SIZE 1024;
#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000

typedef struct _AudioPacket
{
	AVPacketList *first, *last;
	int nb_packets, size;
	SDL_mutex *mutex;
	SDL_cond *cond;
} AudioPacket;


using namespace std;


class VideoManager
{
public:
	//BUILD
	VideoManager(SDL_Window *scr, SDL_Renderer *rend);
	~VideoManager();

	//void exibirInformacaoArquivoVideo(void);
	int alocarMemoria(void);
	int lerFramesVideo(void);
	int criarDisplay(void);

	static int getAudioPacket(AudioPacket*, AVPacket*, int);

	void PlayVideoSequence(string argc);

	
private:

	//void memsetAudioPacket(AudioPacket * pq);
	
	int videoStream;

	//stream de audio
	int audioStream;


	AVFormatContext *pFormatCtx = NULL;


	AVCodecParameters *pCodecParameters = NULL;


	AVCodecParameters *pCodecAudioParameters = NULL;


	AVCodecContext *pCodecCtx = NULL;

	AVCodecContext *pCodecAudioCtx = NULL;

	SDL_AudioSpec wantedSpec = { 0 }, audioSpec = { 0 };

	AVCodec *pCodec = NULL;


	AVCodec *pAudioCodec = NULL;

	AVFrame *pFrame = NULL;

	
	AVFrame *pFrameRGB = NULL;

	
	uint8_t *buffer = NULL;

	
	struct SwsContext *sws_ctx = NULL;


	SDL_Window *screen;

	SDL_Renderer *renderer;

	SDL_Texture* bmp;

	
	void exibirErro(int erro);

	int obterCodecParameters(void);

	int lerCodecVideo(void);

	//int PacketQueuePut(AudioPacket *, const AVPacket *);

	void initAudioPacket(AudioPacket *);

	int putAudioPacket(AudioPacket *, AVPacket *);



};

