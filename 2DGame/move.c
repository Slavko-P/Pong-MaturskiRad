#include "types.h"
#include "audio.h"

/* This routine moves each ball by its motion vector. */
void move_ball() {

	SDL_Log("Ball x: %d, Ball y: %d", ball.x, ball.y);

	/* Move the ball by its motion vector. */
	ball.x += ball.dx;
	ball.y += ball.dy;

	/* Turn the ball around if it hits the edge of the screen. */
	if (ball.x < 0) {
		Play_Score(); //Play when either player gains a point
		score[RIGHT] += 1;
		g_Delay = 1500;
		g_Last_Loss = LEFT;
		init_game();
	}

	if (ball.x > screen->w - 10) {
		Play_Score(); //Play when either player gains a point
		score[LEFT] += 1;
		g_Delay = 1500;
		g_Last_Loss = RIGHT;
		init_game();
	}

	if (ball.y < 0 || ball.y > screen->h - 10) {
		ball.dy = -ball.dy;
		if (Mix_PlayingMusic() == 0) {
			Play_WallHit();
		}
	}

	//check for collision with the paddle
	int i;

	for (i = 0; i < 2; i++) {

		//collision detected	
		if (check_collision(ball, paddle[i])) {
			
			Play_BallPaddleHit();
			
			//ball moving left
			if (ball.dx < 0) {
				ball.dx -= 1;
				//ball moving right
			}
			else {
				ball.dx += 1;
			}

			//change ball direction
			ball.dx = -ball.dx;

			//change ball angle based on where on the paddle it hit
			int hit_pos = (paddle[i].y + paddle[i].h) - ball.y;

			if (hit_pos >= 0 && hit_pos < 7) {
				ball.dy = 4;
			} else if (hit_pos >= 7 && hit_pos < 14) {
				ball.dy = 3;
			} else if (hit_pos >= 14 && hit_pos < 21) {
				ball.dy = 2;
			} else if (hit_pos >= 21 && hit_pos < 28) {
				ball.dy = 1;
			} else if (hit_pos >= 28 && hit_pos < 32) {
				ball.dy = 0;
			} else if (hit_pos >= 32 && hit_pos < 39) {
				ball.dy = -1;
			} else if (hit_pos >= 39 && hit_pos < 46) {
				ball.dy = -2;
			} else if (hit_pos >= 46 && hit_pos < 53) {
				ball.dy = -3;
			} else if (hit_pos >= 53 && hit_pos <= 60) {
				ball.dy = -4;
			}

			//ball moving right
			if (ball.dx > 0) {
				//teleport ball to avoid mutli collision glitch
				if (ball.x < 30) {
					ball.x = 30;
				}
				//ball moving left
			}
			else {
				//teleport ball to avoid mutli collision glitch
				if (ball.x > 600) {
					ball.x = 600;
				}
			}
		}
	}
}

void move_paddle_ai() {

	int center = paddle[LEFT].y + (paddle[LEFT].h /2);
	int screen_center = screen->h / 2 - (paddle[LEFT].h / 2);
	int ball_speed = ball.dy;

	if (ball_speed < 0) {
		ball_speed = -ball_speed;
	}

	//ball moving right
	if (ball.dx > 0) {
		//return to center position
		if (center < screen_center) {
			paddle[LEFT].y += ball_speed;
		}
		else {
			paddle[LEFT].y -= ball_speed;
		}
		//ball moving left
	}
	else {
		//ball moving down
		if (ball.dy > 0) {
			if (ball.y > center) {
				paddle[LEFT].y += ball_speed;
			}
			else {
				paddle[LEFT].y -= ball_speed;
			}
		}

		//ball moving up
		if (ball.dy < 0) {
			if (ball.y < center) {
				paddle[LEFT].y -= ball_speed;
			}
			else {
				paddle[LEFT].y += ball_speed;
			}
		}

		//ball moving stright across
		if (ball.dy == 0) {
			if (ball.y < center) {
				paddle[LEFT].y -= 5;
			}
			else {
				paddle[LEFT].y += 5;
			}
		}
	}
}

void move_paddle(int d, int side) {

	// if shift + down arrow is pressed, move paddle down
	// if the down arrow is pressed move paddle down slower
	// and vice versa
	if (d == -1) {
		if (paddle[side].y >= screen->h - paddle[1].h) {
			paddle[side].y = screen->h - paddle[1].h;
		} 
		else {
			paddle[side].y += 5;
		}
	}
	else if (d == -2) {
		if (paddle[side].y >= screen->h - paddle[1].h) {
			paddle[side].y = screen->h - paddle[1].h;
		}
		else {
			paddle[side].y += 10;
		}
	}

	if (d == 1) {
		if (paddle[side].y <= 0) {
			paddle[side].y = 0;
		}
		else {
			paddle[side].y -= 5;
		}
	}
	else if (d == 2) {
		if (paddle[side].y <= 0) {
			paddle[side].y = 0;
		}
		else {
			paddle[side].y -= 10;
		}
	}
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

void move_all() {
	//paddle ai movement
	move_paddle_ai();
	//Move the balls for the next frame. 
	move_ball();
}