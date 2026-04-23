#include "Tower.hpp"

void Tower::setDamage(float newDamage)
{
	this->mDamage = newDamage;
}

void Tower::setAS(float newAS)
{
	this->mAS = newAS;
}

void Tower::setRange(float newRange)
{
	this->mRange = newRange;
}

float Tower::getDamage()
{
	return this->mDamage;
}

float Tower::getAS()
{
	return this->mAS;
}

float Tower::getRange()
{
	return this->mRange;
}