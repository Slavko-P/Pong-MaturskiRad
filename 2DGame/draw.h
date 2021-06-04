#ifndef PONG_DRAW_H
#define PONG_DRAW_H

extern SDL_Color White;

void draw_all(Uint32 *GameStartTimer);

void draw_game_over(int p);

void draw_menu();

void draw_net();

void draw_ball();

void draw_paddle();

void draw_player_0_score();

void draw_player_1_score();

#endif