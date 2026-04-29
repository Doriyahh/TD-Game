#pragma once
#include "Game.hpp"
#include "Tower.hpp"

class GoodBoyAndy : public Tower {
public:
	GoodBoyAndy(Game*& game, const sf::Vector2f& pos)
		: Tower(game, pos, 1.0f, 70.0f, 150.0f)
	{
		this->setPosition(pos);
		this->mDamage = 1.0f;
		this->mRange = 150.0f;
		this->mAS = 70.0f;
		this->mShootTimer = 0;
		this->mRangeCircle.setRadius(this->mRange);
		this->pTexture->loadFromFile("External/Images/GoodBoyAndy.png");
		this->setTexture(this->pTexture);
		this->mPrice = 225;
	}

	~GoodBoyAndy();

	//Checks if enemy is in range of tower
	bool isEnemyInRange(Enemy*& enemy);

	//Shoots at enemy
	void shootEnemy();

	void update() override;



private:

};