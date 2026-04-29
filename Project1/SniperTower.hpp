#pragma once

#include "Tower.hpp"
#include "Game.hpp"


class CigarAndy : public Tower {
public:
	CigarAndy(Game*& game, const sf::Vector2f& pos)
		: Tower(game, pos, 2.0f, 150.0f, 2000.0f)
	{
		this->setPosition(pos);
		this->mDamage = 2.0f;
		this->mRange = 2000.0f;
		this->mAS = 150.0f;
		this->mShootTimer = 0;
		this->setRotation(sf::Angle(sf::degrees(90)));
		this->mRangeCircle.setRadius(this->mRange);
		this->pTexture->loadFromFile("External/Images/CigarAndy.png");
		this->setTexture(this->pTexture);
		this->mPrice = 350;

		this->getGame()->getLaserVector().push_back(this->mLaser);
		this->mLaser->setFillColor(sf::Color(255, 0, 0, 0));
		this->mLaser->setOrigin(sf::Vector2f(3, 0));
		this->mLaser->setPosition(this->getPosition());
		this->mLaser->setRotation(this->getRotation());
	}

	~CigarAndy();

	bool isEnemyInRange(Enemy*& enemy);

	//Rotates tower toward enemy
	void target(Enemy*& enemy);

	//Shoots at enemy
	void shootEnemy(Enemy*& enemy);

	void update() override;
private:
	sf::RectangleShape* mLaser = new sf::RectangleShape(sf::Vector2f(6, 1000));
};
