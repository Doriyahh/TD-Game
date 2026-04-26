#pragma once

#include "Enemy.hpp"

class BasicEnemy1 : public Enemy 
{
public:

	BasicEnemy1(Game*& mainGame, const std::vector<sf::Vector2f>& wp) : 
	Enemy(mainGame, 3.f, 1.f, 3.f, 3.f, 5.f)
	{
		this->mwaypoints = wp;
		this->setPosition(sf::Vector2f(0.f, 137.5f));
		this->setRadius(30);
		this->setOrigin(sf::Vector2f(30, 30));
		this->setFillColor(sf::Color::Red);
		this->mArmor = 5.0;
	}

	~BasicEnemy1()
	{
		if (this->getHealth() <= 0) {
			this->mGame->removeEnemy(this);
		}
	}

	void update() override
	{
		move();
	}

protected:
	void move() override
	{
		Enemy::move();
	}
};