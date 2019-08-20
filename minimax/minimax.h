#ifndef MINIMAX_H
#define MINIMAX_H

#include <iostream>

using namespace std;

//modifiable
const int mapCount = 9;
const int notFinished = -1;
const int emptyField = 0;
const int player1 = 1;
const int player2 = 2;

class minimax {
public:
	int start(int field_actual[mapCount], int deep, int currentPlayer);

private:
	int max(int deep, int player, int alpha, int beta);
	int min(int deep, int player, int alpha, int beta);
	int win();

	int field[mapCount] = { 0 };
	int maxDeep;
	int perfectMove = -1;
	int startPlayer;
};

#endif