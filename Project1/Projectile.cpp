#include "Projectile.hpp"

bool Projectile::checkHit(Enemy*& enemy)
{
	sf::Vector2f cp1 = this->getPosition();
	sf::Vector2f cp2 = enemy->getPosition();

	float dx = cp1.x - cp2.x;
	float dy = cp1.y - cp2.y;
	float dsquared = (dx * dx) + (dy * dy);

	float combinedRadius = this->getRadius() + enemy->getRadius();
	return dsquared <= (combinedRadius * combinedRadius);
}

bool Projectile::searchEnemy(Enemy* target) {
	// If the pointer itself is null, it definitely doesn't exist in the list
	if (!target) return false;

	// Search the vector of raw pointers
	auto it = std::find_if(this->getHitEnemies().begin(), this->getHitEnemies().end(),
		[target](Enemy* e) {
			return e == target;
		});

	// Returns true if the pointer was found before hitting the end of the vector
	return it != this->getHitEnemies().end();
}

void Projectile::update()
{
	this->move(sf::Vector2f(cos(this->getRotation().asRadians()) * this->mSpeed, sin(this->getRotation().asRadians()) * this->mSpeed));
	for (int i = 0; i < this->mGame->getEnemyVector().size(); i++) {
		if (this->checkHit(this->mGame->getEnemyVector()[i])) {
			if (this->searchEnemy(this->mGame->getEnemyVector()[i])) {
				continue;
			}
			else {
				this->getHitEnemies().push_back(this->mGame->getEnemyVector()[i]);
			}
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
