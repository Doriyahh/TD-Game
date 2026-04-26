#pragma once
#include "Tower.hpp"
#include <cmath>

class glassesAndy : public Tower {
public:
	glassesAndy(Game* game, const sf::Vector2f& pos, const float& Damage = 0.0f, const float& AS = 0.0f, const float& Range = 0.0f, const float& ShootTimer = 0.0f)
		: Tower(game, pos, Damage, AS, Range, ShootTimer)
	{
		this->setPosition(pos);
		this->mDamage = Damage;
		this->mRange = Range;
		this->mAS = AS;
		this->mShootTimer = ShootTimer;
		this->mRangeCircle.setRadius(Range);
	}

	//Checks if enemy is in range of tower
	bool isEnemyInRange(const Enemy& enemy);


	void target(Enemy& enemy);

	//Shoots at enemy
	void shootEnemy();

	void update();

private:

};