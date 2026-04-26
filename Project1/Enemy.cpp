#include "Enemy.hpp"

bool Enemy::isDead() const
{
	return false;
}

void Enemy::move()
{
	//Will check for waypoints and will stop moving if there is none
	if (mwaypoints.empty() || mcurrentwaypoint >= mwaypoints.size())
	{
		return;
	}
		//get target and our position
		sf::Vector2f target = mwaypoints[mcurrentwaypoint];
		sf::Vector2f currentPos = this->getPosition();

		//gets the vector for our current position
		sf::Vector2f direction = target - currentPos;

		//Will get the distance from the target
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		//checks if how close it is to waypoint then will move to the next one
		if (distance < 5.0f)
		{
			mcurrentwaypoint++;
			if (mcurrentwaypoint >= mwaypoints.size())
			{
				reached = true;
				return;
			}
			
		}
		else
		{
			direction /= distance;
			sf::CircleShape::move(direction * mCSpeed);
		}
	
	
	//moves the enemy
}

bool Enemy::reachedEnd() const
{
	return false;
}

void Enemy::update(float deltatime)
{
}
