#include "types.h"
#include "pong.h"

//inisilise starting position and sizes of game elemements
void init_game() {
	ball.x = screen->w / 2;
	ball.y = screen->h / 2;
	ball.w = 10;
	ball.h = 10;
	ball.dy = 1;
	ball.dx = 1;

	paddle[0].x = 20;
	paddle[0].y = screen->h / 2 - 50;
	paddle[0].w = 10;
	paddle[0].h = 50;

	paddle[1].x = screen->w - 20 - 10;
	paddle[1].y = screen->h / 2 - 50;
	paddle[1].w = 10;
	paddle[1].h = 50;
}

int init(int width, int height, int argc, char *args[]) {

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL error:", SDL_GetError()), NULL);
		return 1;
	}
	
	//Initialize SDL TTF
	if (TTF_Init() < 0) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL_TTF error:", TTF_GetError()), NULL);
		return 1;
	}

	//Initialize SDL Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL_mixer error:", Mix_GetError()), NULL);
		return 1;
	}

	int i;

	for (i = 0; i < argc; i++) {
		//Create window	
		if (strcmp(args[i], "-f")) {
			SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);
		}
		else {
			SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
		}
	}

	SDL_ShowCursor(SDL_DISABLE);

	SDL_SetWindowTitle(window, "Pong");

	if (window == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL error:", SDL_GetError()), NULL);
		return 1;
	}

	//create the screen sruface where all the elemnts will be drawn onto (ball, paddles, net etc)
	screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);

	if (screen == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL error:", SDL_GetError()), NULL);
		return 1;
	}

	//create the screen texture to render the screen surface to the actual display
	screen_texture = SDL_CreateTextureFromSurface(renderer, screen);
	if (screen_texture == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL error:", SDL_GetError()), NULL);
		return 1;
	}
	
	//Load the title image
	title = SDL_LoadBMP("title.bmp");
	if (title == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL error:", SDL_GetError()), NULL);
		return 1;
	}

	//Load the numbermap image
	numbermap = SDL_LoadBMP("numbermap.bmp");
	if (numbermap == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL error:", SDL_GetError()), NULL);
		return 1;
	}

	//Load the gameover image
	end = SDL_LoadBMP("gameover.bmp");
	if (end == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL error:", SDL_GetError()), NULL);
		return 1;
	}
	
	Font1 = TTF_OpenFont("FreePixel.ttf", 104);
	if (Font1 == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL_TTF error:", SDL_GetError()), NULL);
		return 1;
	}

	Font2 = TTF_OpenFont("AtariClassic-gry3.ttf" , 20);
	if (Font2 == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL_TTF error:", SDL_GetError()), NULL);
		return 1;
	}

	pongblip1 = Mix_LoadWAV("pongblip1.wav");
	if (pongblip1 == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL_mixer error:", SDL_GetError()), NULL);
		return 1;
	}
	
	pongblip2 = Mix_LoadWAV("pongblip2.wav");
	if (pongblip2 == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL_mixer error:", SDL_GetError()), NULL);
		return 1;
	}

	pongblip3 = Mix_LoadWAV("pongblip3.wav");
	if (pongblip3 == NULL) {
		SDL_ShowSimpleMessageBox(NULL, "Error", catStr("SDL_mixer error:", SDL_GetError()), NULL);
		return 1;
	}

	MainMenu_Pong = TTF_RenderText_Solid(Font1, "Pong", White); //<-test
	
	//TimerString
	Timer_size = snprintf(NULL, 0, "%.2d:%.2d", NULL/*, (ElapsedTime / 60) % 60, ElapsedTime % 60*/) + 1;
	Timer = (char *)malloc(Timer_size);

	// Set the title colourkey. 
	Uint32 colorkey = SDL_MapRGB(title->format, 255, 0, 255);
	SDL_SetColorKey(title, SDL_TRUE, colorkey);
	SDL_SetColorKey(numbermap, SDL_TRUE, colorkey);

	return 0;
}
