#pragma once
#include "Enemy.hpp"
#include "Game.hpp"


class HealerEnemy : public Enemy
{
public: HealerEnemy(Game*& mainGame, const std::vector<sf::Vector2f>& wp) :
	Enemy(mainGame, 7.f, 7.f, 10.f, 2.5f, 2.5f, 30.f)
{


	this->mwaypoints = wp;
	this->setPosition(sf::Vector2f(0.f, 137.5f));
	this->setRadius(15);
	this->setOrigin(sf::Vector2f(15, 15));
	//this->setFillColor(sf::Color::Magenta);
	this->mArmor = 0.0;
	this->pTexture->loadFromFile("External/Images/Claude.png");
	this->setTexture(this->pTexture);
	this->mHealRadius = 50.f;
	this->mHealAmount = 4.f;
}

	  ~HealerEnemy()
	  {
		  if (this->getHealth() <= 0) {
			  this->mGame->removeEnemy(this);
		  }
	  }

	  void HealNearby(std::vector<Enemy*>& enemies);

protected:
	void move() override
	{
		Enemy::move();
	}
private:
	float mHealRadius;
	float mHealAmount;
	float mHealerTimer;
	float mHealerInterval = 120;
};