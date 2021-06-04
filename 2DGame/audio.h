#ifndef PONG_AUDIO_H
#define PONG_AUDIO_H

#ifndef SDL_MIXER_H
#include "sdl_mixer.h"
#endif

//sound mixer
Mix_Music *pongblip[3];
Mix_Music *Sound_Score;

void Play_Score();

void Play_WallHit();

void Play_BallPaddleHit();

#endif