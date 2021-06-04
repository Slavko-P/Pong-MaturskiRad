#ifndef PONG_TYPES_H
#define PONG_TYPES_H

#include <stdio.h>
#include <time.h>
#include <SDL.h>		//SDL2
#include <SDL_ttf.h>	//SDL2 font system

#ifdef _WIN32
#undef main //Potrebno za Visual Studio/Windows
#endif

#define LEFT 0
#define RIGHT 1

#define IN_GAME		1
#define MAIN_MENU	2
#define GAME_OVER	3
#define MULTIPLAYER 4

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
extern int score[];
extern int width, height;		//used if fullscreen
extern paddle_t paddle[2];
extern ball_t ball;

extern SDL_Window *window;		//The window we'll be rendering to
extern SDL_Renderer *renderer;	//The renderer SDL will use to draw to the screen
extern SDL_Event events;		//Used for handling events

//surfaces
extern SDL_Surface *screen;
extern SDL_Surface *numbermap;
extern SDL_Surface *end;

//fonts <-Testing
extern TTF_Font *Font1, *Font2;
SDL_Surface* MainMenu_Pong;

//textures
extern SDL_Texture *screen_texture;

//timer string
extern int Timer_size;
extern char *Timer;
extern Uint32 ElapsedTime;
extern SDL_Surface *timer_surface;

//Globalne varijable
extern int g_Paused;
extern int g_quit;
extern int g_state;
extern int g_Delay;
extern int g_Last_Loss;

#endif