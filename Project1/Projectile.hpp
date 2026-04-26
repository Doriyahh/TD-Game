#pragma once

class Projectile : public sf::CircleShape {
public:
	Projectile(sf::Vector2f& pos, float radius, float degrees, float damage, float speed) : CircleShape(radius) {
		this->setPosition(pos);

		this->setRadius(radius);

		this->setRotation(sf::Angle(sf::degrees(degrees)));

		this->setDamage(damage);

		this->setSpeed(speed);
	}

	void setDamage(float damage) { this->mDamage = damage; }

	void setSpeed(float speed) { this->mSpeed = speed; }

	virtual void update() = 0;
private:
	float mDamage; //Damage projectile will do
	float mSpeed; //Speed of projectile
};