#include <iostream>
#include <ctime>
#include "connect.h"
#include "minimax.h"

using namespace std;

int getMoveFromMap(int map[7]);

int main()
{
	srand(time(NULL));
	int input;
	int currentPlayer = 1;
	int aiPlayer = 1;
	int aiMoves = 10;
	
	cout<<"please select player (1 or 2): ";
	cin>>aiPlayer;
	aiPlayer = aiPlayer == 1 ? 2 : 1;
	cout<<"please choose ai level(2-14): ";
	cin>>aiMoves;
	
	connect game;
	game.reset();
	minimax ai;
	
    RenderWindow window(VideoMode(game.factor * 7, game.factor * 6), "connect four by necaton");

	Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	
	while(window.isOpen())
	{
		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
		
		game.draw(window);	//implements winner
		
		if (game.getWinner() != 0) {
			while (!Mouse::isButtonPressed(Mouse::Button::Left)) {}
			currentPlayer = 1;
			game.reset();
			while (Mouse::isButtonPressed(Mouse::Button::Left)) {}
		}
		
		mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		
		if (currentPlayer == aiPlayer) {	//ai
			int *map = ai.start(game.field, aiMoves, aiPlayer);
			for (int i=0;i<7;i++) if (game.field[i] != 0) map[i] = -2147483647;
			int tempMove = getMoveFromMap(map);
			game.setField(getMoveFromMap(map), aiPlayer);
			currentPlayer = currentPlayer == 1 ? 2 : 1;
			system("cls");
			for (int i=0;i<7;i++) cout<<i+1<<" - "<<map[i]<<endl;
		} else {	//human
			int clickedField = 0;
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				if (mousePos.y > 0 && mousePos.y < game.factor * 6)
					clickedField = mousePos.x / game.factor + 1;
				if (game.setField(clickedField, currentPlayer)) {
					currentPlayer = currentPlayer == 1 ? 2 : 1;
				}
				while (Mouse::isButtonPressed(Mouse::Button::Left)) {}
			}
		}
	}
	return 0;
}

int getMoveFromMap(int map[7])
{
	int highestNumber = -2147483647, randomNumber = 0;
	bool highestNumberMap[7] = {false};
	for (int i=0;i<7;i++)
	{
		if (map[i] > highestNumber) highestNumber = map[i];
	}
	for (int i=0;i<7;i++)
	{
		if (map[i] == highestNumber) highestNumberMap[i] = true;
	}
	do {
		randomNumber = rand()%7;
		if (highestNumberMap[randomNumber] == true) return randomNumber+1;
	} while(true);
	return 0;
}






