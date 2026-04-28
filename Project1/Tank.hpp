#pragma once
#include "Enemy.hpp"

class TankEnemy : public Enemy
{
public: TankEnemy(Game*& mainGame, const std::vector<sf::Vector2f>& wp) :
	Enemy(mainGame,2.f, 2.f, 5.f, 1.f, 1.f, 6.f)
{


	this->mwaypoints = wp;
	this->setPosition(sf::Vector2f(0.f, 137.5f));
	this->setRadius(35);
	this->setOrigin(sf::Vector2f(35, 35));
	this->setFillColor(sf::Color::Blue);
	this->mArmor = 7.0f;

}

	  ~TankEnemy()
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