#include "types.h"

void CheckMiscEvents() {

	while (SDL_PollEvent(&events)) {

		//check for X window press event
		if (events.type == SDL_QUIT) g_quit = 1;

		//check for keyup events
		if (events.type == SDL_KEYUP) {
			switch (events.key.keysym.sym) {
			case SDLK_F2:
				TakeScreenshot();
				break;
			case SDLK_F11:
				if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
					SDL_SetWindowFullscreen(window, SDL_WINDOW_MINIMIZED);
				}
				else if (SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN) {
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
				break;
			case SDLK_ESCAPE:
				g_quit = 1;
				break;
			case SDLK_LCTRL:
				if (g_state == IN_GAME)
					g_Paused = !g_Paused;
				break;
			}
		}
	}
}

int CheckKeyState(int SCANCODE) {

	Uint8 *keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SCANCODE])
		return 1;
	return 0;
}

void Player2_GetArrowsKeystate() {
	Uint8 *keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_DOWN]) {
		move_paddle(-2, RIGHT);
	}
	else if (keystate[SDL_SCANCODE_DOWN]) {
		move_paddle(-1, RIGHT);
	}

	if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_UP]) {
		move_paddle(2, RIGHT);
	}
	else if (keystate[SDL_SCANCODE_UP]) {
		move_paddle(1, RIGHT);
	}
}

void MultiPlayer_GetArrowsKeystate() {
	Uint8 *keystate = SDL_GetKeyboardState(NULL);

	//RIGHT
	if (keystate[SDL_SCANCODE_RSHIFT] && keystate[SDL_SCANCODE_DOWN]) {
		move_paddle(-2, RIGHT);
	}
	else if (keystate[SDL_SCANCODE_DOWN]) {
		move_paddle(-1, RIGHT);
	}

	if (keystate[SDL_SCANCODE_RSHIFT] && keystate[SDL_SCANCODE_UP]) {
		move_paddle(2, RIGHT);
	}
	else if (keystate[SDL_SCANCODE_UP]) {
		move_paddle(1, RIGHT);
	}

	//LEFT
	if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_S]) {
		move_paddle(-2, LEFT);
	}
	else if (keystate[SDL_SCANCODE_S]) {
		move_paddle(-1, LEFT);
	}

	if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_W]) {
		move_paddle(2, LEFT);
	}
	else if (keystate[SDL_SCANCODE_W]) {
		move_paddle(1, LEFT);
	}
}