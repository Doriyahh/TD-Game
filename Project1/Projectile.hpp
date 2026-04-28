#pragma once
#include "Tower.hpp"




class Projectile : public sf::CircleShape {
public:
	Projectile(Game*& game, const sf::Vector2f& pos, float radius, float degrees, float damage, float speed, float pierce) : CircleShape(radius) {
		this->setOrigin(sf::Vector2f(radius, radius));

		this->setPosition(pos);

		this->setRadius(radius);

		this->setRotation(sf::Angle(sf::degrees(degrees)));

		this->setDamage(damage);

		this->setSpeed(speed);

		this->setPierce(pierce);

		this->setGame(game);

		this->setFillColor(sf::Color::Magenta);
	}

	~Projectile() {
	}

	void setDamage(float damage) { this->mDamage = damage; }

	float getDamage() { return this->mDamage; }

	void setSpeed(float speed) { this->mSpeed = speed; }

	void setPierce(float pierce) { this->mPierce = pierce; }

	void setLife(float life) { this->mLife = life; }

	void setGame(Game*& game) { this->mGame = game; }

	void incLife() { this->mLife--; }

	float getPierce() { return this->mPierce; }

	bool checkHit(Enemy*& enemy);

	bool searchEnemy(Enemy* target);

	std::vector<Enemy*>& getHitEnemies() { return this->mHitEnemies; }

	void update();
private:
	Game* mGame;
	std::vector<Enemy*> mHitEnemies;
	float mLife = 100;
	float mDamage; //Damage projectile will do
	float mSpeed; //Speed of projectile
	float mPierce;
};