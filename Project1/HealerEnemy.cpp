#include "HealerEnemy.hpp"

void HealerEnemy::HealNearby(std::vector<Enemy*>& enemies)
{
	sf::Vector2f healerPos = this->getPosition();

	//loop through all enemies on the vector
	for (Enemy* enemy : enemies)
	{
		if (enemy == this)
		{
			continue;
		}

		//distance healer and other enemies
		sf::Vector2f otherPos = enemy->getPosition();
		sf::Vector2f diff = otherPos - healerPos;
		float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);


		if (distance <= mHealRadius)
		{
			float newhealth = enemy->getHealth() + mHealAmount;

			if (newhealth > enemy->getMaxHealth())
			{
				newhealth = enemy->getMaxHealth();
			}

			enemy->setHealth(newhealth);
		}

	}
}