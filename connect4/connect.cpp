#include "connect.h"

void connect::reset()
{
	for (int i=0;i<42;i++) field[i] = 0;
	
	for (int i=0;i<42;i++)
	{
		sfField[i].setSize(Vector2f(factor-1, factor-1));
		sfField[i].setPosition(Vector2f((i%7)*factor, ((i-i%7)/7.f)*factor));
	}
	
	//text
	font.loadFromFile("lucon.ttf");
	for (int i=0;i<3;i++) {
		text[i].setFont(font);
		text[i].setCharacterSize(50);
		text[i].setFillColor(Color(0, 255, 0, 100));
		text[i].setPosition(Vector2f(0, factor * 2));
	}
	text[0].setString("Player 1 wins");
	text[1].setString("Player 2 wins");
	text[2].setString("Draw");
	
	winner = 0;
}

bool connect::setField(int pos, int player)
{	
	if (pos < 1 || pos > 7) return false;
	if (player < 1 || player > 2) return false;
	
	for (int i=5;i>=0;i--)
	{
		if (field[(pos-1)+(i*7)] == 0) {
			field[(pos-1)+(i*7)] = player;
			winner = getWinner();
			return true;
		}
	}
	return false;
}

int connect::getWinner()
{
	//horizontal
	for (int i=0;i<6;i++)
	{
		for (int j=0;j<4;j++)
		{
			if (field[j+(i*7)] == 0) continue;
			if (field[j+(i*7)] == field[j+1+(i*7)] && field[j+1+(i*7)] == field[j+2+(i*7)] && field[j+2+(i*7)] == field[j+3+(i*7)]) {
				return field[j+(i*7)];
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
				return field[i+(j*7)];
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
				return field[i+(j*7)];
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
				return field[i+3+(j*7)];
			}
		}
	}
	for (int i=0;i<42;i++) if (field[i] == 0) return 0;
	return 3;	//draw
}

void connect::draw(RenderWindow &window)
{
	window.clear();
	for (int i=0;i<42;i++)
	{
		if (field[i] == 1) sfField[i].setFillColor(Color(0, 0, 255, 255));
		else if (field[i] == 2) sfField[i].setFillColor(Color(255, 0, 0, 255));
		else sfField[i].setFillColor(Color(30, 30, 30, 255));
	}
	for (int i=0;i<42;i++) window.draw(sfField[i]);
	if (winner != 0) window.draw(text[winner-1]);
	window.display();
}