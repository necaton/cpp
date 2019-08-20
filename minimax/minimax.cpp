#include "minimax.h"

int minimax::start(int field_actual[mapCount], int deep, int currentPlayer)
{
	for (int i = 0; i < mapCount; i++) field[i] = field_actual[i];
	maxDeep = deep;
	startPlayer = currentPlayer;
	max(deep, startPlayer, -2147483647, 2147483647);
	return perfectMove;
}

int minimax::max(int deep, int player, int alpha, int beta)
{
	if (deep <= 0 || win() != notFinished) return win(); //no moves possible
	int maxWert = alpha;
	for (int i = 0; i < mapCount; i++)
	{
		if (field[i] == emptyField) { //next move
			field[i] = player;
			int wert = min(deep - 1, player == player1 ? player2 : player1, maxWert, beta); //recursive
			field[i] = emptyField; //revert
			if (wert > maxWert) { //score
				maxWert = wert;
				if (maxWert >= beta) break;
				if (deep == maxDeep) perfectMove = i; //1st lvl
			}
			if (deep == maxDeep) {
				maxWert = alpha;
				cout<<i<<"-"<<wert<<endl;
			}
		}
	}
	return maxWert;
}

int minimax::min(int deep, int player, int alpha, int beta)
{
	if (deep <= 0 || win() != notFinished) return win(); //no moves possible
	int minWert = beta;
	for (int i = 0; i < mapCount; i++)
	{
		if (field[i] == emptyField) { //next move
			field[i] = player;
			int wert = max(deep - 1, player == player1 ? player2 : player1, alpha, minWert); //recursive
			field[i] = emptyField; //revert
			if (wert < minWert) {
				minWert = wert; //score
				if (minWert <= alpha) break;
			}
		}
	}
	return minWert;
}

int minimax::win()
{
	//************example code for tic tac toe***************************
	int patterns[8][3] = { {0, 1, 2},{3, 4, 5},{6, 7, 8},{0, 3, 6},{1, 4, 7},{2, 5, 8},{0, 4, 8},{2, 4, 6} };
	int winner = 0;
	bool draw = true;

	for (int i = 0; i < 8; i++)
	{
		if (field[patterns[i][0]] == player1 && field[patterns[i][1]] == player1 && field[patterns[i][2]] == player1) winner = player1;
		else if (field[patterns[i][0]] == player2 && field[patterns[i][1]] == player2 && field[patterns[i][2]] == player2) winner = player2;
		if (field[i] == emptyField) draw = false;
	}
	if (winner == player1 && startPlayer == player1 || winner == player2 && startPlayer == player2) return 10;
	else if (winner == player1 && startPlayer == player2 || winner == player2 && startPlayer == player1) return -10;

	if (draw) return 0;
	return notFinished;
}