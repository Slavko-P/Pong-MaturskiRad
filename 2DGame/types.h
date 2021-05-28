#ifndef PONG_TYPES_H
#define PONG_TYPES_H

#include <stdio.h>
#include <time.h>
#include <SDL.h>		//SDL2
#include <SDL_ttf.h>	//SDL2 font system
#include <SDL_mixer.h>	//SDL2 audio

#ifdef _WIN32
#undef main //Needed for WMain to work
#endif

#define SCREEN_WIDTH 640	//window height
#define SCREEN_HEIGHT 480	//window width
//640x480

typedef struct ball_s {
	int x, y;		//position on the screen
	int w, h;		//ball width and height
	int dx, dy;		//movement vector
} ball_t;

typedef struct paddle {
	int x, y;
	int w, h;
} paddle_t;

// Program globals
extern ball_t ball;
extern paddle_t paddle[2];
extern int score[];
extern int width, height;		//used if fullscreen

extern SDL_Window *window;		//The window we'll be rendering to
extern SDL_Renderer *renderer;	//The renderer SDL will use to draw to the screen
extern SDL_Event events;		//Used for handling events

//surfaces
extern SDL_Surface *screen;
extern SDL_Surface *title;
extern SDL_Surface *numbermap;
extern SDL_Surface *end;

//fonts <-Testing
SDL_Color White;
extern TTF_Font *Font1, *Font2;
SDL_Surface* MainMenu_Pong;

extern Uint32 GameStartTime;

//textures
extern SDL_Texture *screen_texture;

//timer string
extern int Timer_size;
extern char *Timer;
extern Uint32 ElapsedTime;
extern SDL_Surface *timer_surface;

//sound mixer
Mix_Music *pongblip1;
Mix_Music *pongblip2;
Mix_Music *pongblip3;

#endif