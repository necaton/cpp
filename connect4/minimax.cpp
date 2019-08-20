#include "minimax.h"

int* minimax::start(int field_actual[mapCount], int deep, int currentPlayer)
{
	for (int i = 0; i < mapCount; i++) field[i] = field_actual[i];
	maxDeep = deep;
	startPlayer = currentPlayer;
	max(deep, startPlayer, -2147483647, 2147483647);
	return moveMap;
}

int minimax::max(int deep, int player, int alpha, int beta)
{
	if (win() != notFinished) return win() * deep;	//no moves possible
	if (deep <= 0) {
		if (win() == notFinished) return 0;
		else return win() * deep;
	}
	
	int maxWert = alpha;
	for (int i = 0; i < 7; i++)
	{
		if (movePossible(i)) { //next move
			move(i, player);
			int wert = min(deep - 1, player == player1 ? player2 : player1, maxWert, beta); //recursive
			move(i, emptyField); //revert
			if (wert > maxWert) { //score
				maxWert = wert;
				//if (deep == maxDeep) perfectMove = i; //1st lvl
				if (maxWert >= beta) break;
			}
			if (deep == maxDeep) {
				moveMap[i] = maxWert;
				maxWert = alpha;
			}
		}
	}
	return maxWert;
}

int minimax::min(int deep, int player, int alpha, int beta)
{
	if (win() != notFinished) return win() * deep;	//no moves possible
	if (deep <= 0) {
		if (win() == notFinished) return 0;
		else return win() * deep;
	}
	
	int minWert = beta;
	for (int i = 0; i < 7; i++)
	{
		if (movePossible(i)) { //next move
			move(i, player);
			int wert = max(deep - 1, player == player1 ? player2 : player1, alpha, minWert); //recursive
			move(i, emptyField); //revert
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
	int temp = notFinished;
	//horizontal
	for (int i=0;i<6;i++)
	{
		for (int j=0;j<4;j++)
		{
			if (field[j+(i*7)] == 0) continue;
			if (field[j+(i*7)] == field[j+1+(i*7)] && field[j+1+(i*7)] == field[j+2+(i*7)] && field[j+2+(i*7)] == field[j+3+(i*7)]) {
				temp = field[j+(i*7)];
				if (temp == player1 && startPlayer == player1 || temp == player2 && startPlayer == player2) return 10;	//startPlayer wins
				else if (temp == player1 && startPlayer == player2 || temp == player2 && startPlayer == player1) return -10;	//startPlayer loses
			}
		}
	}
	//vertikal
	for (int i=0;i<7;i++)
	{
		for (int j=0;j<3;j++)
		{
			if (field[i+(j*7)] == 0) continue;
			if (field[i+(j*7)] == field[i+((j+1)*7)] && field[i+((j+1)*7)] == field[i+((j+2)*7)] && field[i+((j+2)*7)] == field[i+((j+3)*7)]) {
				temp = field[i+(j*7)];
				if (temp == player1 && startPlayer == player1 || temp == player2 && startPlayer == player2) return 10;	//startPlayer wins
				else if (temp == player1 && startPlayer == player2 || temp == player2 && startPlayer == player1) return -10;	//startPlayer loses
			}
		}
	}
	//diagonal
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<3;j++)
		{
			//down
			if (field[i+(j*7)] == 0) continue;
			if (field[i+(j*7)] == field[i+1+((j+1)*7)] && field[i+1+((j+1)*7)] == field[i+2+((j+2)*7)] && field[i+2+((j+2)*7)] == field[i+3+((j+3)*7)]) {
				temp = field[i+(j*7)];
				if (temp == player1 && startPlayer == player1 || temp == player2 && startPlayer == player2) return 10;	//startPlayer wins
				else if (temp == player1 && startPlayer == player2 || temp == player2 && startPlayer == player1) return -10;	//startPlayer loses
			}
		}
	}
	
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<3;j++)
		{
			//up
			if (field[i+3+(j*7)] == 0) continue;
			if (field[i+3+(j*7)] == field[i+2+((j+1)*7)] && field[i+2+((j+1)*7)] == field[i+1+((j+2)*7)] && field[i+1+((j+2)*7)] == field[i+0+((j+3)*7)]) {
				temp = field[i+3+(j*7)];
				if (temp == player1 && startPlayer == player1 || temp == player2 && startPlayer == player2) return 10;	//startPlayer wins
				else if (temp == player1 && startPlayer == player2 || temp == player2 && startPlayer == player1) return -10;	//startPlayer loses
			}
		}
	}
	
	if (temp == player1 && startPlayer == player1 || temp == player2 && startPlayer == player2) return 10;	//startPlayer wins
	else if (temp == player1 && startPlayer == player2 || temp == player2 && startPlayer == player1) return -10;	//startPlayer loses
	
	for (int i=0;i<mapCount;i++) if (field[i] == 0) return notFinished;	//not finished
	
	return 0;	//draw
}

bool minimax::movePossible(int position)
{
	if (position < 0 || position > 6) return false;
	for (int i=5;i>=0;i--)
	{
		if (field[position+(i*7)] == 0) {
			return true;
		}
	}
	return false;
}

bool minimax::move(int position, int player)
{
	if (player == emptyField) {	//undo move
		for (int i=4;i>=0;i--)
		{
			if (field[position+(i*7)] == emptyField) {
				field[position+((i+1)*7)] = emptyField;
				return true;
			}
			if (i==0) field[position+(i*7)] = emptyField;
		}
	} else {	//set move
		for (int i=5;i>=0;i--)
		{
			if (field[position+(i*7)] == emptyField) {
				field[position+(i*7)] = player;
				return true;
			}
		}
	}
	return false;
}