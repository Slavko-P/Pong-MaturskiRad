#include "types.h"
#include "init.h"
#include "move.h"
#include "draw.h"
#include "audio.h"

int score[] = { 0,0 };
int width, height;

ball_t ball;
paddle_t paddle[2];

SDL_Window *window = NULL;	
SDL_Renderer *renderer;		
SDL_Event events;

SDL_Surface *screen;
SDL_Surface *title;
SDL_Surface *numbermap;
SDL_Surface *end;

SDL_Texture *screen_texture;

SDL_Color White = { 255, 255, 255 };
TTF_Font *Font1, *Font2;
SDL_Surface* surfaceMessage;

Uint32 GameStartTime = -1;

char *catStr(char *str1, char *str2) {
	int BufferSize = strlen(str1) + strlen(str2) + sizeof(char)*2; //space + term
	char *NewString = (char *)malloc(BufferSize);
	snprintf(NewString, BufferSize, "%s %s", str1, str2);
	return NewString;
}

int check_score() {

	int i;

	//loop through player scores
	for (i = 0; i < 2; i++) {

		//check if score is @ the score win limit
		if (score[i] == 10) {

			//reset scores
			score[0] = 0;
			score[1] = 0;

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

//if return value is 1 collision occured. if return is 0, no collision.
int check_collision(ball_t a, paddle_t b) {

	int left_a, left_b;
	int right_a, right_b;
	int top_a, top_b;
	int bottom_a, bottom_b;

	left_a = a.x;
	right_a = a.x + a.w;
	top_a = a.y;
	bottom_a = a.y + a.h;

	left_b = b.x;
	right_b = b.x + b.w;
	top_b = b.y;
	bottom_b = b.y + b.h;


	if (left_a > right_b) {
		return 0;
	}

	if (right_a < left_b) {
		return 0;
	}

	if (top_a > bottom_b) {
		return 0;
	}

	if (bottom_a < top_b) {
		return 0;
	}

	return 1;
}

int main(int argc, char *args[]) {
	
	//SDL Window setup
	if (init(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args) == 1) {
		return 0;
	}

	SDL_GetWindowSize(window, &width, &height);

	int sleep = 0;
	int quit = 0;
	int state = 0;
	int r = 0;
	Uint32 next_game_tick = SDL_GetTicks();

	// Initialize the ball position data. 
	init_game();

	//render loop
	while (quit == 0) {

		if (state == 1 && GameStartTime == -1) {
			GameStartTime = SDL_GetTicks(); //<--testing, not final
		}

		//check for new events every frame
		SDL_PumpEvents();

		//check for x press event
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit = 1;
		}

		const Uint8 *keystate = SDL_GetKeyboardState(NULL);

		if (keystate[SDL_SCANCODE_ESCAPE]) {
			quit = 1;
		}

		if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_DOWN]) {
			move_paddle(-2);
		}
		else if (keystate[SDL_SCANCODE_DOWN]) {
			move_paddle(-1);
		}
		
		if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_UP]) {
			move_paddle(2);
		}
		else if (keystate[SDL_SCANCODE_UP]) {
			move_paddle(1);
		}
		
		if (keystate[SDL_SCANCODE_F11]) {
			if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
				SDL_SetWindowFullscreen(window, SDL_WINDOW_MINIMIZED);
			}
			else if (SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN) {
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}
			SDL_Delay(500);
		}

		//draw background
		SDL_RenderClear(renderer);
		SDL_FillRect(screen, NULL, 0x000000ff);

		//display main menu
		if (state == 0) {

			if (keystate[SDL_SCANCODE_SPACE]) {
				state = 1;
			}
			
			draw_text(Font1, "test", White);

			//draw menu 
			draw_menu();

			//display gameover
		}
		else if (state == 2) {

			if (keystate[SDL_SCANCODE_SPACE]) {
				state = 0;
				//delay for a little bit so the space bar press dosnt get triggered twice
				//while the main menu is showing
				SDL_Delay(500);
			}

			if (r == 1) {
				//if player 1 is AI if player 1 was human display the return value of r not 3
				draw_game_over(3);
			}
			else {
				//display gameover
				draw_game_over(r);
			}

			//display the game
		}
		else if (state == 1) {

			//check score
			r = check_score();

			//if either player wins, change to game over state
			if (r == 1) {
				state = 2;
			}
			else if (r == 2) {
				state = 2;
			}

			//draw_text("Pong", Font1, White);
			//draw_text("Press space to begin", Font, White);
			//paddle ai movement
			move_paddle_ai();
			//* Move the balls for the next frame. 
			move_ball();

			//draw timer (testing)
			draw_timer();

			//draw net
			draw_net();
			//draw paddles
			draw_paddle();
			//* Put the ball on the screen.
			draw_ball();
			//draw the score
			draw_player_0_score();
			//draw the score
			draw_player_1_score();
		}

		SDL_UpdateTexture(screen_texture, NULL, screen->pixels, screen->w * sizeof(Uint32));
		SDL_RenderCopy(renderer, screen_texture, NULL, NULL);

		//draw to the display
		SDL_RenderPresent(renderer);

		//time it takes to render  frame in milliseconds
		next_game_tick += 1000 / 60;
		sleep = next_game_tick - SDL_GetTicks();

		if (sleep >= 0) {
			SDL_Delay(sleep);
		}
	}

	//free loaded images
	SDL_FreeSurface(screen);
	SDL_FreeSurface(title);
	SDL_FreeSurface(numbermap);
	SDL_FreeSurface(end);
	SDL_FreeSurface(surfaceMessage); //<-Testing

	//free renderer and all textures used with it
	SDL_DestroyRenderer(renderer);

	//Destroy window 
	SDL_DestroyWindow(window);

	//Quit TTF subsystems
	TTF_Quit();

	//Quit SDL subsystems 
	SDL_Quit();

	return 0;
}
