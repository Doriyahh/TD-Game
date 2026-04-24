#include "Enemy.hpp"

bool Enemy::isDead() const
{
	//returns true or false depending on whether the enemy is dead or not
	if (this->mHealth <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::damageTaken(float amount)
{
	//checks the damaage a tower has done to it and applies that damage to their health bar
}

bool Enemy::reachedEnd() const
{
	//gets the position of the enemy and chekcs to see if that position intersects with the ending waypoint
}

void Enemy::move(float time)
{
	//moves the enemy
}
