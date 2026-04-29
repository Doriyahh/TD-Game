#include "BasicTower.hpp"


glassesAndy::~glassesAndy()
{
}

//Calculates difference in positions of tower and enemy and determines if enemy is within tower range through arithmetic
//Generative AI used to derive function formula
bool glassesAndy::isEnemyInRange(Enemy*& enemy)
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

//Changes rotation of tower to point towards enemy
void glassesAndy::target(Enemy*& enemy)
{
	sf::Vector2f enemyPos = enemy->getPosition();
	sf::Vector2f towerPos = this->getPosition();

	//Get the direction the enemy is moving
	sf::Vector2f targetWaypoint = enemy->getWaypoints()[enemy->getCurrentWaypoint()];
	sf::Vector2f moveDir = targetWaypoint - enemyPos;

	//Normalize the direction
	float dist = std::sqrt(moveDir.x * moveDir.x + moveDir.y * moveDir.y);
	if (dist != 0) {
		moveDir /= dist;
	}

	//Lead the target
	//Leading by a factor of the enemy's speed 
	float leadDistance = enemy->getCSpeed() * (sqrt((enemyPos.x - towerPos.x) * (enemyPos.x - towerPos.x)) / 12.0f);
	sf::Vector2f predictedPos = enemyPos + (moveDir * leadDistance);

	//Calculate rotation toward the PREDICTED position
	float dx = predictedPos.x - towerPos.x;
	float dy = predictedPos.y - towerPos.y;
	float rotation = std::atan2f(dy, dx);

	sf::Angle a1(sf::radians(rotation));

	this->setRotation(a1);
}

void glassesAndy::shootEnemy()
{
    // Convert sf::Angle to a plain float (degrees) for the Projectile constructor
    float rotationDegrees = this->getRotation().asDegrees();

    // Create projectile on the stack and push it into the game's projectile vector
	if (!this->getUp1()) {
		Projectile* newProjectile = new Projectile(this->getGame(), this->getPosition(), 8.0f, rotationDegrees, this->getDamage(), 12.0f, 2.0f);
		this->getGame()->getProjectileVector().push_back(newProjectile);
	}
	else {
		Projectile* newProjectile = new Projectile(this->getGame(), this->getPosition(), 8.0f, rotationDegrees, this->getDamage(), 12.0f, 2.0f);
		this->getGame()->getProjectileVector().push_back(newProjectile);
		newProjectile = new Projectile(this->getGame(), this->getPosition(), 8.0f, rotationDegrees - 10, this->getDamage(), 12.0f, 2.0f);
		this->getGame()->getProjectileVector().push_back(newProjectile);
		newProjectile = new Projectile(this->getGame(), this->getPosition(), 8.0f, rotationDegrees + 10, this->getDamage(), 12.0f, 2.0f);
		this->getGame()->getProjectileVector().push_back(newProjectile);
	}
}

void glassesAndy::update()
{
	//Updates shoot timer
	if (mShootTimer > 0.0f)
	{
		mShootTimer--;
	}
	if (this->getUp2() && this->mAS != 50) {
		this->mAS = 50;
	}

	//Goes through all enemies in game and checks if theyre in range, shoots at first one it finds in range, if any
	//Only does this if shoot timer is expired
	if (mShootTimer <= 0) {
		for (int i = 0; i < this->getGame()->getEnemyVector().size(); i++) {
			if (isEnemyInRange(this->getGame()->getEnemyVector()[i])) {
				target(this->getGame()->getEnemyVector()[i]);
				shootEnemy();
				mShootTimer = mAS;
				break;
			}
		}
		
	}
	
}
