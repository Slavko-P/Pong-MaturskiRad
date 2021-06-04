#include "types.h"
#include "init.h"
#include "move.h"
#include "draw.h"
#include "userinput.h"

#define SCREEN_WIDTH 640	//window height
#define SCREEN_HEIGHT 480	//window width

int score[] = { 0,0 };
int width, height;

int g_Delay;
int g_Last_Loss = RIGHT;
int g_Paused = 0;
int g_quit = 0;
int g_state = MAIN_MENU;

paddle_t paddle[2];
ball_t ball;

SDL_Window *window;	
SDL_Renderer *renderer;		
SDL_Event events;

SDL_Surface *screen;
SDL_Surface *numbermap;
SDL_Surface *end;

SDL_Texture *screen_texture;

TTF_Font *Font1, *Font2;
SDL_Surface* surfaceMessage;

int check_score() {

	int i;
	//loop through player scores
	for (i = 0; i < 2; i++) {

		//check if score is @ the score win limit
		if (score[i] == 10) {

			//reset scores
			score[LEFT] = 0;
			score[RIGHT] = 0;

			//return 1 if player 1 score @ limit
			if (i == 0) {
				return 1;
				//return 2 if player 2 score is @ limit
			}
			else {
				return 2;
			}
		}
	}
	//return 0 if no one has reached a score of 10 yet
	return 0;
}

int main(int argc, char *args[]) {

	ball_t ball;
	paddle_t paddle[2];

	Uint32 GameStartTime = -1;

	//SDL Window setup
	if (init(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args)) {
		return 0;
	}

	int sleep = 0;
	int r = 0;
	Uint32 next_game_tick = SDL_GetTicks();

	// Initialize the ball position data. 
	init_game(&ball, &paddle);

	//render loop
	while (!g_quit) {

		while (g_Paused) {
			CheckMiscEvents();
			next_game_tick = SDL_GetTicks();
			g_Delay = 0;
			SDL_Delay(1);
		} 
		
		if (g_Delay > 0) {
			SDL_Delay(g_Delay);
			next_game_tick = SDL_GetTicks();
			g_Delay = 0;
		} 
		else {
			next_game_tick += 1000 / 60;
			sleep = next_game_tick - SDL_GetTicks();
			if (sleep >= 0) {
				SDL_Delay(sleep);
			}
		} 

		SDL_PumpEvents();
		//Provera za 'X' dugme na prozor, F2, F11, Esc, Space
		CheckMiscEvents();

		draw_backround();

		//display main menu
		if (g_state == MAIN_MENU) {
			if (CheckKeyState(SDL_SCANCODE_SPACE)) {
				g_state = IN_GAME;
			}
			if (CheckKeyState(SDL_SCANCODE_M)) {
				g_state = MULTIPLAYER;
			}

			//draw menu 
			draw_menu();
		}
		else if (g_state == GAME_OVER) { //display gameover

			if (CheckKeyState(SDL_SCANCODE_SPACE)) {
				g_state = MAIN_MENU;
			}

			if (r == 1) {
				//if player 1 is AI if player 1 was human display the return value of r not 3
				draw_game_over(3);
			}
			else {
				//display gameover
				draw_game_over(r);
			}	
		}
		else if (g_state == IN_GAME) { //display the game

			if (GameStartTime == -1) {
				GameStartTime = SDL_GetTicks();
			}

			Player2_GetArrowsKeystate();

			//check score
			r = check_score();

			//if either player wins, change to game over state
			if (r == 1 || r == 2) {
				g_state = GAME_OVER;
			}

			//Move objects
			move_all(ball, paddle);
			//Draw object
			draw_all(&GameStartTime, ball, paddle);
		}
		else if (g_state = MULTIPLAYER) {
			if (GameStartTime == -1) {
				GameStartTime = SDL_GetTicks();
			}
			
			MultiPlayer_GetArrowsKeystate();
			move_ball();
			//Draw object
			draw_all(&GameStartTime, ball, paddle);
		}

		SDL_UpdateTexture(screen_texture, NULL, screen->pixels, screen->w * sizeof(Uint32));
		SDL_RenderCopy(renderer, screen_texture, NULL, NULL);

		//draw to the display
		SDL_RenderPresent(renderer);
	}

	//free loaded images
	SDL_FreeSurface(screen);
	SDL_FreeSurface(numbermap);
	SDL_FreeSurface(end);
	SDL_FreeSurface(surfaceMessage); //<-Testing

	//free renderer and all textures used with it
	SDL_DestroyRenderer(renderer);
	//Destroy window 
	SDL_DestroyWindow(window);

	//Quit TTF subsystems
	TTF_Quit();
	//Quit Mix sybsystems
	Mix_Quit();
	//Quit SDL subsystems 
	SDL_Quit();

	return 0;
}
