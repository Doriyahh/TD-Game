#pragma once
#include "Game.hpp"
#include "Tower.hpp"

class GoodBoyAndy : public Tower {
public:
	GoodBoyAndy(Game*& game, const sf::Vector2f& pos)
		: Tower(game, pos, 1.0f, 90.0f, 100.0f)
	{
		this->setPosition(pos);
		this->mDamage = 1.0f;
		this->mRange = 70.0f;
		this->mAS = 70.0f;
		this->mShootTimer = 0;
		this->mRangeCircle.setRadius(this->mRange);
		this->pTexture->loadFromFile("External/Images/GoodBoyAndy.png");
		this->setTexture(this->pTexture);
		this->mPrice = 300;

		game->getTowerVector().push_back(this);
	}

	~GoodBoyAndy();

	//Checks if enemy is in range of tower
	bool isEnemyInRange(Enemy*& enemy);

	//Shoots at enemy
	void shootEnemy();

	void update() override;



private:

};