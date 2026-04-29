#pragma once
#include "Enemy.hpp"
#include "Game.hpp"


class TankEnemy : public Enemy
{
public: TankEnemy(Game*& mainGame, const std::vector<sf::Vector2f>& wp) :
	Enemy(mainGame,2.f, 2.f, 75.f, 2.f, 2.f, 45.f)
{


	this->mwaypoints = wp;
	this->setPosition(sf::Vector2f(0.f, 137.5f));
	this->setRadius(35);
	this->setOrigin(sf::Vector2f(35, 35));
	//this->setFillColor(sf::Color::Blue);
	this->pTexture->loadFromFile("External/Images/SFML.png");
	this->setTexture(this->pTexture);
	this->mArmor = 11.0f;

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