#pragma once
#include <SFML/Graphics.hpp>
#include "Path.hpp"
#include <vector>

class Map : public sf::RectangleShape
{
public:
	Map();
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape background;
	std::vector<Path> paths;
	std::vector<sf::Vector2f> waypoints;
};
