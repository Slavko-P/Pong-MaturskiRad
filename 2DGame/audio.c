#include "audio.h"

void Play_Score() {
	Mix_PlayChannel(-1, Sound_Score, 0);
}

void Play_WallHit() {
	Mix_PlayChannel(-1, pongblip[0], 0);
}

void Play_BallPaddleHit() {

	if (Mix_PlayingMusic() == 0) {

		srand(time(0));

		switch (rand() % 3) {
		case 0:
			Mix_PlayChannel(-1, pongblip[0], 0);
			break;
		case 1:
			Mix_PlayChannel(-1, pongblip[1], 0);
			break;
		case 2:
			Mix_PlayChannel(-1, pongblip[2], 0);
			break;
		}
	}
}