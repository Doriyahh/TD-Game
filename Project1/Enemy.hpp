#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"


//PLEASE READ IF WORKING ON ENEMIES!!!
/*
When instantiating an enemy, please add it to the game enemy vector.
This is NOT a "Vector2f" from sf, this is a C++ specific data structure, acting as an array-linked list hybrid
You do this by doing "mainGame.getEnemyVector().push_back('your_enemy');"
You will need access to the mainGame object wherever you want to call it, but this is necessary for keeping track of
all enemies in the game state. Similarly, when an enemy "dies", you will need to call
"mainGame->getEnemyVector().erase('your_enemy');" - As far as I understand it, this will automatically search for that
specific enemy within the vector and remove it, so this will need to be called within the enemy destructor or update function.
This should not interfere with any systems you want to add to your enemies, just a supplementary thing you can add to a constructor,
given you have access to the mainGame object.
A similar thing will be implemented for all temporary objects within the game.

- Brock
*/


class Enemy : public sf::CircleShape
{
public:
	Enemy(Game*& mainGame,float MaxHealth, float Health, float Damage, float MaxSpeed, float CSpeed, float Gold)
		: sf::CircleShape(30)
		{
			this->setOrigin(sf::Vector2f(30, 30));
			this->mMaxHealth = MaxHealth;
			this->mHealth = Health;
			this->mDamage = Damage;
			this->mMaxSpeed = MaxSpeed;
			this->mCSpeed = CSpeed;
			this->mGold = Gold;
			this->mGame = mainGame;
		}

	virtual ~Enemy()
	{
		isDead();

		//delete enemy here
	
	}

	float getMaxHealth()
	{
		return this->mMaxHealth;
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
	void SetMaxHealth(float newMaxHealth)
	{
		this->mMaxHealth = newMaxHealth;
	}

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
	std::vector<sf::Vector2f>& getWaypoints() { return this->mwaypoints; }
	int getCurrentWaypoint() { return this->mcurrentwaypoint; }

	virtual bool isDead() const;
	virtual bool reachedEnd() const;
	virtual void update();
	virtual void move();

protected:

	float mMaxHealth;
	float  mHealth;
	float  mDamage;
	float mMaxSpeed;
	float mCSpeed;//current speed
	float mGold;// reward for killing enemy
	float mArmor = 0; // do we want flat rate or percentage
	float mStun = 0; // complelety stops enemy
	Game* mGame = nullptr;


	sf::Texture mTexture;

	sf::Texture* pTexture = &mTexture;


	bool dead = false;
	bool reached =false;
	bool stunned = false;

	std::vector<sf::Vector2f> mwaypoints;
	int mcurrentwaypoint = 0;
};
