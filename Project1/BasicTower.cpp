#include "BasicTower.hpp"


glassesAndy::~glassesAndy()
{
	this->mGame->removeTower(this);
}

//Calculates difference in positions of tower and enemy and determines if enemy is within tower range through arithmetic
//Generative AI used to derive function formula
bool glassesAndy::isEnemyInRange(Enemy*& enemy)
{
	//Gets vector for actual tower center
	sf::Vector2f cp1 = this->getRangeCircle().getPosition();
	//Gets vector for actual enemy center
	sf::Vector2f cp2 = enemy->getPosition() + sf::Vector2f(enemy->getRadius(), enemy->getRadius());

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

//Changes rotation of tower to point towards enemy
void glassesAndy::target(Enemy*& enemy)
{
	sf::Vector2f enemyPos = enemy->getPosition() + sf::Vector2f(enemy->getRadius(), enemy->getRadius());
	sf::Vector2f towerPos = this->getPosition();

	float dx = enemyPos.x - towerPos.x;
	float dy = enemyPos.y - towerPos.y;

	float rotation = std::atan2f(dy, dx) * 180 / 3.14159265;

	sf::Angle a1(sf::degrees(rotation));

	this->setRotation(a1);
}

void glassesAndy::shootEnemy()
{
    // Convert sf::Angle to a plain float (degrees) for the Projectile constructor
    float rotationDegrees = this->getRotation().asDegrees();

    // Create projectile on the stack and push it into the game's projectile vector
    Projectile* newProjectile = new Projectile(this->getGame(), this->getPosition(), 5.0f, rotationDegrees, this->getDamage(), 7.0f);
    this->getGame()->getProjectileVector().push_back(newProjectile);
}

void glassesAndy::update()
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
				target(this->getGame()->getEnemyVector()[i]);
				shootEnemy();
				break;
			}
		}
		mShootTimer = mAS;
	}
	
}
