#include "Projectile.hpp"

bool Projectile::checkHit(Enemy*& enemy)
{
	sf::Vector2f cp1 = this->getPosition();
	sf::Vector2f cp2 = enemy->getPosition() + sf::Vector2f(enemy->getRadius(), enemy->getRadius());

	float dx = cp1.x - cp2.x;
	float dy = cp1.y - cp2.y;
	float dsquared = (dx * dx) + (dy * dy);

	float combinedRadius = this->getRadius() + enemy->getRadius();
	return dsquared <= (combinedRadius * combinedRadius);
}

void Projectile::update()
{
	this->move(sf::Vector2f(cos(this->getRotation().asRadians()) * this->mSpeed, sin(this->getRotation().asRadians()) * this->mSpeed));
	for (int i = 0; i < this->mGame->getEnemyVector().size(); i++) {
		if (this->checkHit(this->mGame->getEnemyVector()[i])) {
			if (this->mGame->getEnemyVector()[i]->getArmor() > 0) {
				this->mGame->getEnemyVector()[i]->setArmor(this->mGame->getEnemyVector()[i]->getArmor() - 1);
			}
			else {
				this->mGame->getEnemyVector()[i]->setHealth(this->mGame->getEnemyVector()[i]->getHealth() - this->getDamage());
			}
			this->setPierce(this->getPierce() - 1);
		 }
	}
	this->incLife();
	if (this->mLife <= 0 || this->getPierce() <= 0) {
		this->mGame->removeProjectile(this);
	}
}
