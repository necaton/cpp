#ifndef SHADOW_H
#define SHADOW_H

#include "SFML/Graphics.hpp"
#include <math.h>
#include <vector>

class shadow {
public:
	shadow(sf::Vector2f screen);
	void addLine(sf::Vector2f line1, sf::Vector2f line2);
	void draw(sf::RenderWindow &window, sf::Vector2f position);
private:
	struct collisionPoints {
		collisionPoints(sf::Vector2f v1, sf::Vector2f v2) { p1 = v1; p2 = v2; }
		sf::Vector2f p1;
		sf::Vector2f p2;
	};
	std::vector<collisionPoints> CollisionData;
	sf::Vector2f screenSize;
	const float pi = 3.1415926535f;
};

#endif