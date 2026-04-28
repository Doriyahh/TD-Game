#include "SniperTower.hpp"

CigarAndy::~CigarAndy()
{
}

bool CigarAndy::isEnemyInRange(Enemy*& enemy)
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
void CigarAndy::target(Enemy*& enemy)
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


void CigarAndy::shootEnemy(Enemy*& enemy)
{
	sf::Vector2f enemyPos = enemy->getPosition();
	sf::Vector2f towerPos = this->getPosition();

	//Calculate rotation toward the enemy position
	float dx = enemyPos.x - towerPos.x;
	float dy = enemyPos.y - towerPos.y;
	float distance = sqrt((dx * dx) + (dy * dy));

	//Set laser length to distance between tower and enemy
	this->mLaser->setSize(sf::Vector2f(6, distance));
	this->mLaser->setPosition(this->getPosition());
	this->mLaser->setRotation(this->getRotation() - sf::degrees(90));
	//Makes laser fully opaque
	this->mLaser->setFillColor(sf::Color(255, 0, 0, 255));
}

void CigarAndy::update()
{
	//Updates shoot timer
	if (mShootTimer > 0.0f)
	{
		mShootTimer--;
	}
	if (this->mLaser->getFillColor().a > 0) {
		this->mLaser->setFillColor(sf::Color(255, 0, 0, this->mLaser->getFillColor().a - 3));
	}

	//Goes through all enemies in game and checks if theyre in range, shoots at first one it finds in range, if any
	//Only does this if shoot timer is expired
	if (mShootTimer <= 0) {
		if (!this->getGame()->getEnemyVector().empty()) {
			target(this->getGame()->getEnemyVector()[0]);
			shootEnemy(this->getGame()->getEnemyVector()[0]);
			if (this->getGame()->getEnemyVector()[0]->getArmor() <= 0) {
				this->getGame()->getEnemyVector()[0]->setHealth(this->getGame()->getEnemyVector()[0]->getHealth() - 3);
			}
			else {
				this->getGame()->getEnemyVector()[0]->setArmor(this->getGame()->getEnemyVector()[0]->getArmor() - 1);
			}
			mShootTimer = mAS;
		}
	}

}