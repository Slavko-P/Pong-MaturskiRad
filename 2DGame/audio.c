#include "types.h"

void Play_BallPaddleHit() {
	
	if (Mix_PlayingMusic() == 0) {
		
		srand(time(0));

		switch (rand() % 3) {
		case 0:
			Mix_PlayChannel(-1, pongblip1, 0);
			break;
		case 1:
			Mix_PlayChannel(-1, pongblip2, 0);
			break;
		case 2:
			Mix_PlayChannel(-1, pongblip3, 0);
			break;
		default:
			Mix_PlayChannel(-1, pongblip1, 0);
			break;
		}
	}
}