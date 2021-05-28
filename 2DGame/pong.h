#ifndef PONG_H
#define PONG_H

#include "types.h"

char *catStr(char *str1, char *str2);

int check_score();

int check_collision(ball_t a, paddle_t b);

#endif