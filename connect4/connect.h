#ifndef CONNECT_H
#define CONNECT_H

#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class connect {
public:
	void reset();
	bool setField(int pos, int player);
	int getWinner();
	void draw(RenderWindow &window);
	
	int field[42];
	float factor = 80;
	
private:
	RectangleShape sfField[42];
	Font font;
	Text text[3];
	int winner;
};

#endif

// 0- 1- 2- 3- 4- 5- 6
// 7- 8- 9-10-11-12-13
//14-15-16-17-18-19-21
//21-22-23-24-25-26-27
//28-29-30-31-32-33-34
//35-36-37-38-39-40-41

//0=empty;1=player1,2=player2