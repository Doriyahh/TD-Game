#pragma once
#include <SFML/Graphics.hpp>

class Enemy : public sf::CircleShape
{
public:
	Enemy(float Health = 0.0, float Damage = 0.0, float MaxSpeed = 0.0, float CSpeed = 0.0, float Gold = 0.0) : sf::CircleShape(30)
	{

		this->mHealth = Health;
		this->mDamage = Damage;
		this->mMaxSpeed = MaxSpeed;
		this->mCSpeed = CSpeed;
		this->mGold = Gold;
	}
	virtual ~Enemy()
	{
		isDead();

		//delete enemy here
	}
	float getHealth()
	{
		return this->mHealth;
	}

	float getDamage()
	{
		return this->mDamage;
	}

	float getMaxSpeed()
	{
		return this->mMaxSpeed;
	}
	
	float getCSpeed()
	{
		return this->mCSpeed;
	}

	float getGold()
	{
		return this->mGold;
	}

	float getArmor()
	{
		return this->mArmor;
	}

	float getStun()
	{
		return this->mStun;
	}
	//setters
	void setHealth(float newHealth)
	{
		this->mHealth = newHealth;
	}

	void setDamage(float newDamage)
	{
		this->mDamage = newDamage;
	}

	void setMaxSpeed(float newMaxSpeed)
	{
		this->mMaxSpeed = newMaxSpeed;
	}

	void setCSpeed(float newCSpeed)
	{
		this->mCSpeed = newCSpeed;
	}

	void setGold(float newGold)
	{
		this->mGold = newGold;
	}

	void setArmor(float newArmor)
	{
		this->mArmor = newArmor;

	}
	void setStun(float newStun)
	{
		this->mStun = newStun;
	}
	virtual bool isDead() const;
	virtual void damageTaken(float amount);
	virtual bool reachedEnd() const;

protected:

	virtual  void move(float time);
	float  mHealth;
	float  mDamage;
	float mMaxSpeed;
	float mCSpeed;//current speed
	float mGold;// reward for killing enemy
	float mArmor; // do we want flat rate or percentage
	float mStun; // for complete stop not slow

	
}
