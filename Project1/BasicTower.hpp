#pragma once
#include "Tower.hpp"
#include "Game.hpp"


class glassesAndy : public Tower {
public:
	glassesAndy(Game*& game, const sf::Vector2f& pos)
		: Tower(game, pos, 1.0f, 90.0f, 100.0f)
	{
		this->setPosition(pos);
		this->mDamage = 1.0f;
		this->mRange = 90.0f;
		this->mAS = 100.0f;
		this->mShootTimer = 0;
		this->setRotation(sf::Angle(sf::degrees(180)));
		this->mRangeCircle.setRadius(this->mRange);
		this->pTexture->loadFromFile("External/Images/GlassesAndy.png");
		this->setTexture(this->pTexture);
		this->mPrice = 150;
	}

	~glassesAndy();

	//Checks if enemy is in range of tower
	bool isEnemyInRange(Enemy*& enemy);


	void target(Enemy*& enemy);

	//Shoots at enemy
	void shootEnemy();

	void update() override;

	

private:

};