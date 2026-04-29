#pragma once

#include "Enemy.hpp"
#include "Game.hpp"

class BasicEnemy1 : public Enemy 
{
public:

	BasicEnemy1(Game*& mainGame, const std::vector<sf::Vector2f>& wp) : 
	Enemy(mainGame,4.f, 10.f, 10.f, 3.f, 3.f, 15.f)
	{
		this->mwaypoints = wp;
		this->setPosition(sf::Vector2f(0.f, 137.5f));
		this->setRadius(30);
		this->setOrigin(sf::Vector2f(30, 30));
		//this->setFillColor(sf::Color::Red);
		this->pTexture->loadFromFile("External/Images/ChatGPT.png");
		this->setTexture(this->pTexture);
		this->mArmor = 0.0;
	}

	~BasicEnemy1()
	{
		if (this->getHealth() <= 0) {
			this->mGame->removeEnemy(this);
		}
	}

protected:
	void move() override
	{
		Enemy::move();
	}
};