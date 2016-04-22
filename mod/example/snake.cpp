/*
 * snake.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: Jake Vandereay
 */
#include "snake.h"
#include "cel/ui.h"
#include <string.h>
#include "cel/utilfn.h"
namespace mod_snake {

template <class T>
void shiftBack(T array[], uint8_t len) {
	T tmp;
	for (uint8_t i = len-1; i>0;i--) {
		tmp = array[i-1];
		array[i] = tmp;
	}
}

Snake::Snake():
	hijackUI(false),
	loopT(),
	timer2(),
	snake(),
	direction(right),
	lastDirection(right),
	food(),
	len(0)
	{
		setup();
	}
Snake::~Snake() {}


void Snake::setup() {
	/*
	 * ~Init code~
	 * The point of this rather than just using the constructor
	 * is to make porting to dynamic modules later easier.
	 */
	ui.PushItem(F("Start Snake ->"), this);//add menu entry
	Spin::RegisterTask(this);//register bg task
}
void Snake::callback(cel::menucallbackinfo_t &info) {
	if (info.button == right) {
		start();
		PLF("snake game started");
	}
}
void Snake::start() {
	hijackUI = true;//enable drawing
	ui.frozen = true;//tell UI to stop

	//init char tiles
	resetTiles();
	//prep game
	resetGame();

	////setup display////
	//clear display
	ClearSection(0, 0, 16, ui.lcd);
	ClearSection(0, 1, 16, ui.lcd);
	//draw game tiles
	ui.lcd.setCursor(0,0);
	ui.lcd.write(0xff);//wall
	ui.lcd.write(byte(0));//x1y1
	ui.lcd.write(byte(1));//x2y1
	ui.lcd.write(0xff);//wall
	ui.lcd.setCursor(0,1);
	ui.lcd.write(0xff);//wall
	ui.lcd.write(byte(2));//x1y2
	ui.lcd.write(byte(3));//x2y2
	ui.lcd.write(0xff);//wall

}
void Snake::exit() {
	hijackUI = false;//stop drawing
	ui.frozen = false;//tell ui to start again
	ui.UpdateScreen(); //tell the ui to refresh
}
void Snake::task() {
	if(hijackUI)
		game();
}
void Snake::resetGame() {
	//reset the snake
	for(uint8_t i=0;i<snakeMaxLen;i++)
		snake[i] = Coord();//copy new blank Coord objects onto the array
	//reset the directions
	direction = right;
	lastDirection = right;
	//other
	len = 3;//starting length
	food.x = random(9);
	food.y = random(17);
}

void Snake::game() {
	btndir_t dpad = DPad();
	if (dpad != none && dpad != center) {
		direction = dpad;
		lastDirection = direction;
	} else {
		direction = lastDirection;
		}
	if (loopT.Every(200)) {
		Coord head;
		//snake thingy section
		if (dpad == center)
			exit();//quit game
//		resetTiles();
		//remove end end of snake
		Coord &end = (len < snakeMaxLen) ? snake[len-1] : snake[snakeMaxLen-1];
		placeDot(end.x, end.y, 0);
		shiftBack(snake, snakeMaxLen);//inch snake array forward
		if (direction == right) //direction handling
			if(snake[0].x < width-1)//bounds check
				snake[0].x++;
			else
				die();//die if wall it hit
		else if(direction == left)
			if(snake[0].x >0)
				snake[0].x--;
			else
				die();
		else if(direction == down)
			if(snake[0].y < height-1)
				snake[0].y++;
			else
				die();
		else if(direction == up)
			if(snake[0].y >0)
				snake[0].y--;
			else
				die();
		//did we get food?
		if (snake[0] == food){
			len++;//grow
			//move the food
			food.x = random(9);
			food.y = random(17);
		}
		placeDot(food.x, food.y, true);//print the tasty dot
		//print snake
		for(uint8_t i=0; i<snakeMaxLen && i<len; i++) {
			placeDot(snake[i].x, snake[i].y, 1);
			if(i != 0 && snake[i] == snake[0])//did the snake crash into itself?
				die();
		}
		//print score
		ui.lcd.setCursor(5, 1);
		ui.lcd.print(F("score "));
		ui.lcd.print(len-3);//assuming starting len is 3
		//did you win?
		if (len >= snakeMaxLen) {
			ui.lcd.setCursor(5, 0);
			ui.lcd.print(F("You Win!"));
		}
		drawGame();
	}
}
void Snake::placeDot(uint8_t x, uint8_t y, bool s) {
	uint8_t dot = B0010000;//create dot var. dot is shifted to the rightmost space
//	if(!s)
//		dot = ~dot;//inverse mask
	if (x >= 10 || y >= 18) {
		//out of bounds check
		PLF("Snake::placeDot | error out of bounds");
		return;
	}
	if (x<5) {
		dot = dot >> uint8_t(x);//shift dot to the correct x pos
		if (y < 8) {
			//tile1
			if(s)
				tile1[y] = tile1[y] | dot;//add dot to tile
			else
				tile1[y] = tile1[y] & ~dot;//remove dot
			ui.lcd.createChar(0,tile1);
		} else {
			y = y-8;
			//tile3
			if(s)
				tile3[y] = tile3[y] | dot;
			else
				tile3[y] = tile3[y] & ~dot;
			ui.lcd.createChar(2,tile3);
		}
	} else {
		x = x - 5;//offset x for 0 index
		dot = dot >> x;
		if (y < 8) {
			//tile2
			if(s)
				tile2[y] = tile2[y] | dot;
			else
				tile2[y] = tile2[y] & ~dot;
			ui.lcd.createChar(1,tile2);
		} else {
			y = y-8;
			//tile4
			if(s)
				tile4[y] = tile4[y] | dot;
			else
				tile4[y] = tile4[y] & ~dot;
			ui.lcd.createChar(3,tile4);
		}
	}

}
void Snake::resetTiles() {
	char clear[8] = {0};//create an array of zeros
	memcpy(&tile1, &clear, 8);//copy it to the tiles
	memcpy(&tile2, &clear, 8);
	memcpy(&tile3, &clear, 8);
	memcpy(&tile4, &clear, 8);
	//push them to the lcd
	ui.lcd.createChar(0,tile1);
	ui.lcd.createChar(1,tile2);
	ui.lcd.createChar(2,tile3);
	ui.lcd.createChar(3,tile4);
}
void Snake::drawGame() {
}
void Snake::die() {
	exit();
}
void setup() {
	Snake* snake = new Snake;
}
}//ns end_snake
