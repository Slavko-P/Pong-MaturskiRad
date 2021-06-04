#include "types.h"
#include "draw.h"

SDL_Color White = { 255,255,255 };

int Timer_size;
char *Timer;

void draw_TitleText() {
	
	SDL_Rect dest;

	dest.x = (screen->w / 2) - (MainMenu_Pong->w / 2);
	dest.y = (screen->h / 2) - 100;
	dest.w = screen->w;
	dest.h = screen->h;

	SDL_BlitSurface(MainMenu_Pong, NULL, screen, &dest);
}

void draw_timer(Uint32 *GameStartTime) {

	Uint32 ElapsedTime;
	SDL_Surface *timer_surface;

	SDL_Rect dest;

	dest.x = (screen->w / 2) - 50;
	dest.y = 15;
	dest.w = 48;
	dest.h = 48;

	ElapsedTime = (SDL_GetTicks() - *GameStartTime) / 1000;

	snprintf(Timer, Timer_size, "%.2d:%.2d", (ElapsedTime / 60) % 60, ElapsedTime % 60);

	timer_surface = TTF_RenderText_Solid(Font2, Timer, White);

	SDL_BlitSurface(timer_surface, NULL, screen, &dest);

	SDL_FreeSurface(timer_surface);
}

void draw_backround() {
	//draw background
	SDL_RenderClear(renderer);
	SDL_FillRect(screen, NULL, 0x000000ff);
}

void draw_game_over(int p) {

	SDL_Rect p1;
	SDL_Rect p2;
	SDL_Rect cpu;
	SDL_Rect dest;

	p1.x = 0;
	p1.y = 0;
	p1.w = end->w;
	p1.h = 75;

	p2.x = 0;
	p2.y = 75;
	p2.w = end->w;
	p2.h = 75;

	cpu.x = 0;
	cpu.y = 150;
	cpu.w = end->w;
	cpu.h = 75;

	dest.x = (screen->w / 2) - (end->w / 2);
	dest.y = (screen->h / 2) - (75 / 2);
	dest.w = end->w;
	dest.h = 75;

	switch (p) {

	case 1:
		SDL_BlitSurface(end, &p1, screen, &dest);
		break;
	case 2:
		SDL_BlitSurface(end, &p2, screen, &dest);
		break;
	default:
		SDL_BlitSurface(end, &cpu, screen, &dest);
	}
}

void draw_menu() {
	draw_TitleText();
}

void draw_net() {

	int i;
	SDL_Rect net;

	net.x = screen->w / 2;
	net.y = 45;
	net.w = 1;
	net.h = 10;

	//draw the net
	for (i = 0; i < 29; i++) {

		if (SDL_FillRect(screen, &net, 0xffffffff) != 0) {
			printf("Fill rectangle faliled in func draw_net()");
		}

		net.y = net.y + 15;
	}
}

void draw_ball() {

	SDL_Rect src;

	src.x = ball.x;
	src.y = ball.y;
	src.w = ball.w;
	src.h = ball.h;

	if (SDL_FillRect(screen, &src, 0xffffffff) != 0) {
		printf("Fill rectangle faliled in func drawball()");
	}
}

void draw_paddle() {

	int i;
	SDL_Rect src;

	for (i = 0; i < 2; i++) {

		src.x = paddle[i].x;
		src.y = paddle[i].y;
		src.w = paddle[i].w;
		src.h = paddle[i].h;

		if (SDL_FillRect(screen, &src, 0xffffffff) != 0) {
			printf("Fill rectangle faliled in func draw_paddle()");
		}
	}
}

void draw_player_0_score() {

	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 64;
	src.h = 64;

	dest.x = (screen->w / 2) - src.w - 200; //12 is padding spacing
	dest.y = 0;
	dest.w = 64;
	dest.h = 64;

	if (score[0] > 0 && score[0] < 10) {
		src.x += src.w * score[0];
	}

	SDL_BlitSurface(numbermap, &src, screen, &dest);
}

void draw_player_1_score() {

	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 64;
	src.h = 64;

	dest.x = (screen->w / 2) + 200;
	dest.y = 0;
	dest.w = 64;
	dest.h = 64;

	if (score[1] > 0 && score[1] < 10) {
		src.x += src.w * score[1];
	}

	SDL_BlitSurface(numbermap, &src, screen, &dest);
}

void draw_all(Uint32 *GameStartTime) {
	//draw timer 
	draw_timer(GameStartTime);
	//draw net
	draw_net();
	//draw paddles
	draw_paddle();
	//Put the ball on the screen.
	draw_ball();
	//draw the score
	draw_player_0_score();
	//draw the score
	draw_player_1_score();
}