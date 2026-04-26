#pragma once
#include "Tower.hpp"



class Projectile : public sf::CircleShape {
public:
	Projectile(Game*& game, const sf::Vector2f& pos, float radius, float degrees, float damage, float speed) : CircleShape(radius) {
		this->setPosition(pos);

		this->setRadius(radius);

		this->setRotation(sf::Angle(sf::degrees(degrees)));

		this->setDamage(damage);

		this->setSpeed(speed);
	}

	~Projectile() {
		this->mGame->removeProjectile(this);
	}

	void setDamage(float damage) { this->mDamage = damage; }

	void setSpeed(float speed) { this->mSpeed = speed; }

	void update();
private:
	Game* mGame;
	float mDamage; //Damage projectile will do
	float mSpeed; //Speed of projectile
};