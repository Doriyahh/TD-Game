#pragma once
#include "Tower.hpp"
#include <cmath>

class glassesAndy : public Tower {
public:
	glassesAndy(Game*& game, const sf::Vector2f& pos, float Damage, float AS, float Range)
		: Tower(game, pos, Damage, AS, Range)
	{
		this->setPosition(pos);
		this->mDamage = Damage;
		this->mRange = Range;
		this->mAS = AS;
		this->mShootTimer = 0;
		this->setRotation(sf::Angle(sf::degrees(180)));
		this->mRangeCircle.setRadius(Range);
		this->pTexture->loadFromFile("External/Images/GlassesAndy.png");
		this->setTexture(this->pTexture);

		game->getTowerVector().push_back(this);
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