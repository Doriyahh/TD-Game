#pragma once

#include "Enemy.hpp"

class BossEnemy : public Enemy
{
public:
	BossEnemy(Game*& mainGame, const std::vector<sf::Vector2f>& wp) :
		Enemy(mainGame,18.f, 18.f, 5.f, 2.f, 2.f, 10.f)
	{
		this->mwaypoints = wp;
		this->setPosition(sf::Vector2f(0.f, 137.5f));
		this->setRadius(40);
		this->setOrigin(sf::Vector2f(40, 40));
		this->setFillColor(sf::Color::White);
		this->pTexture->loadFromFile("External/Images/Visual.png");
		this->setTexture(this->pTexture);
		this->mArmor = 0.0;
	}

	~BossEnemy()
	{
		if (this->getHealth() <= 0) {
			this->mGame->removeEnemy(this);
		}
	}

protected:
	void move() override
	{
		float healthRatio = this->mHealth / 18.f;
		this->mCSpeed = 2.f * (1.0f + (1.0f - healthRatio) * 1.5f);
		Enemy::move();
	}
};