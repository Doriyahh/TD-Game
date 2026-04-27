#pragma once

#include "Enemy.hpp"

class Boss : public Enemy
{
public:
	Boss(Game*& mainGame, const std::vector<sf::Vector2f>& wp) :
		Enemy(mainGame, 18.f, 3.f, 2.f, 2.f, 10.f)
	{
		this->mwaypoints = wp;
		this->setPosition(sf::Vector2f(0.f, 137.5f));
		this->setRadius(40);
		this->setOrigin(sf::Vector2f(40, 40));
		this->setFillColor(sf::Color::White);
		this->mArmor = 0.0;
	}

	~Boss()
	{
		if (this->getHealth() <= 0) {
			this->mGame->removeEnemy(this);
		}
	}

protected:
	void move() override
	{
		float healthRatio = this->mHealth / 18;

		this->mCSpeed = 2.f * (1.f + (1.f - healthRatio) * 1.5f);

		Enemy::move();
	}

};