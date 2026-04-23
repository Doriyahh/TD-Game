#pragma once
#include "Map.hpp"

class Path : public sf::RectangleShape
{
public:

	Path(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& Color) :
		sf::RectangleShape(size)
	{
		this->setPosition(pos);
		this->setFillColor(Color);
	}
};