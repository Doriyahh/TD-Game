#pragma once
#include <SFML/Graphics.hpp>
#include "Path.hpp"
#include <vector>

class Map : public sf::RectangleShape
{
public:
	Map();
	void draw(sf::RenderWindow& window);

	// So you guys can access the waypoints from outside the class and use them for enemy movement
	const std::vector<sf::Vector2f>& getWaypoints() const;
	// Returns waypoints as a vector of sf::Vector2f

private:
	sf::RectangleShape background;
	std::vector<Path> paths;
	std::vector<sf::Vector2f> waypoints;
};
