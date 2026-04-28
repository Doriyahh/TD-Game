#include "SniperTower.hpp"

CigarAndy::~CigarAndy()
{
	this->mGame->removeTower(this);
}

//Changes rotation of tower to point towards enemy
void CigarAndy::target(Enemy*& enemy)
{
	sf::Vector2f enemyPos = enemy->getPosition();
	sf::Vector2f towerPos = this->getPosition();

	//Calculate rotation toward the enemy position
	float dx = enemyPos.x - towerPos.x;
	float dy = enemyPos.y - towerPos.y;
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