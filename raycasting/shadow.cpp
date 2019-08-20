#include "shadow.h"

shadow::shadow(sf::Vector2f screen)
{
	screenSize = screen;
	addLine(sf::Vector2f(0, 0), sf::Vector2f(screen.x, 0));
	addLine(sf::Vector2f(0, 0), sf::Vector2f(0, screen.y));
	addLine(sf::Vector2f(screen.x, 0), sf::Vector2f(screen.x, screen.y));
	addLine(sf::Vector2f(0, screen.y), sf::Vector2f(screen.x, screen.y));
}

void shadow::addLine(sf::Vector2f line1, sf::Vector2f line2)
{
	CollisionData.push_back(collisionPoints(line1, line2));
}

void shadow::draw(sf::RenderWindow &window, sf::Vector2f position)
{
	std::vector<float> angles;
	std::vector<sf::Vector2f> EndPoints;
	float offset = 0.001f;
	//set angle
	for (unsigned int i = 0; i < CollisionData.size(); i++)
	{
		sf::Vector2f v[2] = { CollisionData.at(i).p1 , CollisionData.at(i).p2 };
		for (int j = 0; j < 2; j++)
		{
			float erg = atan2(v[j].x - position.x, (v[j].y - position.y)*-1) * 180 / pi;
			if (erg < 0) erg += 360;
			angles.push_back(erg - offset < 0 ? erg - offset + 360 : erg - offset);
			angles.push_back(erg + offset >= 360 ? erg + offset - 360 : erg + offset);
		}
	}
	//sort angle
	bool swapp = true;
	while (swapp)
	{
		swapp = false;
		for (unsigned int i = 0; i < angles.size() - 1; i++)
		{
			if (angles.at(i) > angles.at(i + 1)) {
				float temp = angles.at(i + 1);
				angles.at(i + 1) = angles.at(i);
				angles.at(i) = temp;
				swapp = true;
			}
		}
	}
	//get long endpoints from angle
	for (unsigned int i = 0; i < angles.size(); i++)
	{
		EndPoints.push_back(sf::Vector2f(
			position.x + (screenSize.x + screenSize.y) * sin(angles.at(i)*pi / 180),
			position.y + (screenSize.x + screenSize.y) * cos(angles.at(i)*pi / 180) * -1));
	}
	//get endpoint from collisions
	for (unsigned int j = 0; j < angles.size(); j++)
	{
		for (unsigned int i = 0; i < CollisionData.size(); i++)
		{
			sf::Vector2f v1 = CollisionData.at(i).p1, v2 = CollisionData.at(i).p2, v3 = EndPoints.at(j), v4 = position, result;
			result.x = round((((v4.x - v3.x)*(v2.x*v1.y - v1.x*v2.y) - (v2.x - v1.x)*(v4.x*v3.y - v3.x*v4.y)) /
				((v4.y - v3.y)*(v2.x - v1.x) - (v2.y - v1.y)*(v4.x - v3.x))) * 10000) / 10000;
			result.y = round((((v1.y - v2.y)*(v4.x*v3.y - v3.x*v4.y) - (v3.y - v4.y)*(v2.x*v1.y - v1.x*v2.y)) /
				((v4.y - v3.y)*(v2.x - v1.x) - (v2.y - v1.y)*(v4.x - v3.x))) * 10000) / 10000;
			if (!((((v1.x <= v2.x) && (result.x < v1.x || result.x > v2.x)) ||
				((v1.x > v2.x) && (result.x > v1.x || result.x < v2.x)) ||
				((v1.y <= v2.y) && (result.y < v1.y || result.y > v2.y)) ||
				((v1.y > v2.y) && (result.y > v1.y || result.y < v2.y))) || 
				abs(v3.x - v4.x) < abs(v3.x - result.x) && abs(v3.y - v4.y) < abs(v3.y - result.y)) &&
				sqrt(pow(v4.x - result.x, 2) + pow(v4.y - result.y, 2)) < sqrt(pow(v4.x - v3.x, 2) + pow(v4.y - v3.y, 2))) {
				EndPoints.at(j) = result;
			}
		}
	}
	//draw
	for (unsigned int i = 0; i < EndPoints.size(); i++)
	{
		sf::VertexArray Triangle(sf::Triangles, 3);
		sf::Vector2f TriangleArray[3] = { position, EndPoints.at(i), (i >= EndPoints.size() - 1) ? EndPoints.at(0) : EndPoints.at(i + 1) };
		for (int j = 0; j < 3; j++) {
			Triangle[j].position = TriangleArray[j];
			Triangle[j].color = sf::Color(255, 255, 255, 255);
			Triangle[j].texCoords = TriangleArray[j];
		}
		window.draw(Triangle);
	}
}