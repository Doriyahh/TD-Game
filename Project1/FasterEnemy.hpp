#pragma once
#include "Enemy.hpp"

class FastEnemy : public Enemy
{
public: FastEnemy(Game*& mainGame, const std::vector<sf::Vector2f>& wp) :
	Enemy(mainGame,3.f, 3.f, 3.f, 5.f, 5.f, 5.f)
	{
	
	
		this->mwaypoints = wp;
		this->setPosition(sf::Vector2f(0.f, 137.5f));
		this->setRadius(30);
		this->setOrigin(sf::Vector2f(30, 30));
		//this->setFillColor(sf::Color::Green);
		this->pTexture->loadFromFile("External/Images/Gemini.png");
		this->setTexture(this->pTexture);
		this->mArmor = 0.0;
	
	}

	~FastEnemy()
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
