#include "AoeTower.hpp"

GoodBoyAndy::~GoodBoyAndy()
{
	this->mGame->removeTower(this);
}

//Calculates difference in positions of tower and enemy and determines if enemy is within tower range through arithmetic
//Generative AI used to derive function formula
bool GoodBoyAndy::isEnemyInRange(Enemy*& enemy)
{
	//Gets vector for actual tower center
	sf::Vector2f cp1 = this->getRangeCircle().getPosition();
	//Gets vector for actual enemy center
	sf::Vector2f cp2 = enemy->getPosition();

	//Pythagorean theorem for actual distance between tower and enemy
	float dx = cp1.x - cp2.x;
	float dy = cp1.y - cp2.y;
	float dSquared = (dx * dx) + (dy * dy);

	//Compares actual distance between tower and enemy to combined radius.
	//If combined radius is greater than distance, enemy is within range
	//Avoids using sqrt function for efficiency, compares squared values
	float combinedRadius = this->getRangeCircle().getRadius() + enemy->getRadius();
	return dSquared <= (combinedRadius * combinedRadius);
}

void GoodBoyAndy::shootEnemy()
{
	float rotationDegrees = 0;

	// Create projectiles on the stack and push it into the game's projectile vector
	for (int i = 0; i < 8; i++) {
		Projectile* newProjectile = new Projectile(this->getGame(), this->getPosition(), 5.0f, rotationDegrees, this->getDamage(), 12.0f, 2.0f);
		newProjectile->setLife(20.0f);
		this->getGame()->getProjectileVector().push_back(newProjectile);
		rotationDegrees += 45.0f;
	}
}

void GoodBoyAndy::update()
{
	//Updates shoot timer
	if (mShootTimer > 0.0f)
	{
		mShootTimer--;
	}

	//Goes through all enemies in game and checks if theyre in range, shoots at first one it finds in range, if any
	//Only does this if shoot timer is expired
	if (mShootTimer <= 0) {
		for (int i = 0; i < this->getGame()->getEnemyVector().size(); i++) {
			if (isEnemyInRange(this->getGame()->getEnemyVector()[i])) {
				shootEnemy();
				mShootTimer = mAS;
				break;
			}
		}

	}

}