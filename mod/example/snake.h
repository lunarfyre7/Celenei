/*
 * snake.h
 *
 *  Created on: Dec 11, 2015
 *      Author: Jake Vandereay
 */

#ifndef SNAKE_H_
#define SNAKE_H_
#include "../base/modulebase.h"
#include "cel/timer.h"
/*
 * Bare bones snake game for Celenei
 * Uses a 2x2 grid of custom chars on an lcd display to draw the game
 */
namespace mod_snake {

const int width = 10;//don't change w/h without changing the placedot code
const int height = 16;
#define snakeMaxLen 20


struct Coord {
	Coord(): x(0), y(0), en(false) {}
	uint8_t x;
	uint8_t y;
	bool en;
	bool inline operator==(Coord& b) {
		return (x == b.x && y == b.y);
	}
};
class Snake: public Module, public UIcallback, Spin::Task {
public:
	Snake();
	~Snake();

	void setup();//module setup code
	void callback(cel::menucallbackinfo_t&);//ui callback
	void task();//normal loop task

private:
	bool hijackUI;
	//tiles for the game
	unsigned char tile1[8];//x1y1
	unsigned char tile2[8];//x2y1
	unsigned char tile3[8];//x1y2
	unsigned char tile4[8];//x2y2
	Coord snake[snakeMaxLen];
	Coord food;
	uint8_t len; //the actual length of the snake
	btndir_t direction;
	btndir_t lastDirection;
	cel::Timer loopT;
	cel::Timer timer2;


	void game();//game loop
	void start();//start game
	void exit();//end game
	void placeDot(uint8_t, uint8_t, bool);
	//place dot at x/y
	//the bool arg is the color (true for black)
	//works as a 10x16 grid with 0 index.
	void resetTiles();//reset tiles
	void resetGame();//reset the game state
	void drawGame();//draw the game
	void die();
};

void setup();

}//ns end_snake
#endif /* SNAKE_H_ */
