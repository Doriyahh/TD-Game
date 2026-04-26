#pragma once

#include <SFML/Graphics.hpp>

class Enemy : public sf::CircleShape
{
public:
	Enemy(Game*& mainGame, float Health = 0.0, float Damage = 0.0, float MaxSpeed = 0.0, float CSpeed = 0.0, float Gold = 0.0, std::vector<sf::Vector2f> waypoints= {})
		: sf::CircleShape(30)
		{
			this->mHealth = Health;
			this->mDamage = Damage;
			this->mMaxSpeed = MaxSpeed;
			this->mCSpeed = CSpeed;
			this->mGold = Gold;
			this->mGame = mainGame;
				//this->mGame->getEnemyVector().push_back(*this); *PUT THIS IN SUBCLASS CONSTRUCTORS*
			this->mwaypoints = waypoints;
			this->mcurrentwaypoint  = 0;
		}

	virtual ~Enemy()
	{
		if (this->getHealth() <= 0)
		{
			this->mGame->removeEnemy(this); //Removes enemy from list *OVERIDE FOR SUBCLASSES AND COPY*

		}
	
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

	virtual void damageTaken(float amount);
	virtual bool reachedEnd() const;
	virtual void update(float deltatime);

protected:

	virtual  void move(float deltatime);
	float  mHealth;
	float  mDamage;
	float mMaxSpeed;
	float mCSpeed;//current speed
	float mGold;// reward for killing enemy
	float mArmor = 1; // do we want flat rate or percentage
	float mStun = 0; // complelety stops enemy
	Game* mGame;

	bool dead = false;
	bool reached =false;
	bool stunned = false;

	std::vector<sf::Vector2f> mwaypoints;
	int mcurrentwaypoint = 0;
};
