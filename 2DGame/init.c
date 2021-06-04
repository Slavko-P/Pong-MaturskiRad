#include "types.h"
#include "pong.h"
#include "audio.h"
#include "draw.h"

//inisilise starting position and sizes of game elemements
void init_game() {
	
	paddle[LEFT].x = 20;
	paddle[LEFT].y = screen->h / 2 - 50;
	paddle[LEFT].w = 10;
	paddle[LEFT].h = 50;

	paddle[RIGHT].x = screen->w - 20 - 10;
	paddle[RIGHT].y = screen->h / 2 - 50;
	paddle[RIGHT].w = 10;
	paddle[RIGHT].h = 50;

	ball.w = 10;
	ball.h = 10;
	//ball.dy = 2;
	//ball.dx = 2;

	ball.x = (screen->w / 2) - (ball.w / 2);
	//ball.y = screen->h / 2;

	//Player that lost last round, serves
	switch (g_Last_Loss) {
	case LEFT:
		ball.dx = -3;
		break;
	case RIGHT:
		ball.dx = 3;
		break;
	}

	srand(time(0));

	//Random ball start from top or bottom
	switch (rand() % 2) {
	case 0: 
		ball.y = 0;
		ball.dy = 3;
		break;
	case 1:
		ball.y = screen->h - ball.h;
		ball.dy = -3;
		break;
	}
}

int init(int width, int height, int argc, char *args[]) {

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}
	
	//Initialize SDL TTF
	if (TTF_Init() < 0) {
		SDL_ShowSimpleMessageBox(NULL, "Error", TTF_GetError(), NULL);
		return 1;
	}

	//Initialize SDL Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_ShowSimpleMessageBox(NULL, "Error", Mix_GetError(), NULL);
		return 1;
	}

	int i;

	for (i = 0; i < argc; i++) {
		//Create window	
		if (strcmp(args[i], "-fullscreen") == 0 || strcmp(args[i], "-f") == 0) {
			SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
			break;
		}
	}

	if (argc == i) {
		SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
	}

	SDL_ShowCursor(SDL_DISABLE);

	SDL_SetWindowTitle(window, "Pong");

	if (window == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}

	//create the screen sruface where all the elemnts will be drawn onto (ball, paddles, net etc)
	screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);

	if (screen == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}

	//create the screen texture to render the screen surface to the actual display
	screen_texture = SDL_CreateTextureFromSurface(renderer, screen);
	if (screen_texture == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}
	
	//Load the numbermap image
	numbermap = SDL_LoadBMP("numbermap.bmp");
	if (numbermap == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}

	//Load the gameover image
	end = SDL_LoadBMP("gameover.bmp");
	if (end == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}
	
	Font1 = TTF_OpenFont("FreePixel.ttf", 104);
	if (Font1 == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}

	Font2 = TTF_OpenFont("AtariClassic-gry3.ttf" , 20);
	if (Font2 == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}

	pongblip[0] = Mix_LoadWAV("pongblip1.wav");
	if (pongblip[0] == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}
	
	pongblip[1] = Mix_LoadWAV("pongblip2.wav");
	if (pongblip[1] == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}

	pongblip[2] = Mix_LoadWAV("pongblip3.wav");
	if (pongblip[2] == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}

	Sound_Score = Mix_LoadWAV("score.wav");
	if (Sound_Score == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", SDL_GetError(), NULL);
		return 1;
	}
	
	Mix_Volume(-1, 80);

	MainMenu_Pong = TTF_RenderText_Solid(Font1, "Pong", White);

	//TimerString
	Timer_size = snprintf(NULL, 0, "%.2d:%.2d", NULL);
	Timer = (char *)malloc(Timer_size);

	// Set the title colourkey. 
	Uint32 colorkey = SDL_MapRGB(numbermap->format, 255, 0, 255);
	SDL_SetColorKey(numbermap, SDL_TRUE, colorkey);

	return 0;
}
