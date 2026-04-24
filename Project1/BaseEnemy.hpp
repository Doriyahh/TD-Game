#pragma once

#include "Enemy.hpp"

class BasicEnemy : public Enemy 
{
public:
	BasicEnemy(float Health = 3.0, float Damage = 1.0, float maxSpeed = 2.0, float Gold = 5.0) : Enemy(Health, Damage, maxSpeed, 0, Gold)
	{
		this->mHealth = Health;
		this->mDamage = Damage;
		this->mMaxSpeed = maxSpeed;
		this->mGold = Gold;
	}
	
};