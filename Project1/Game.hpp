#pragma once
#include <vector>
#include "Enemy.hpp"
#include "Tower.hpp"
#include "Projectile.hpp"

// Primary class for player values. May also end up containing game wrapper.
class Game {
public:
	int getGold(void) { return this->mPlayerGold; }
	int getHealth(void) { return this->mPlayerHealth; }
	void setGold(int input) { this->mPlayerGold = input; }
	void setHealth(int input) { this->mPlayerHealth = input; }
	std::vector<Enemy>& getEnemyVector() { return this->enemies; }
	std::vector<Projectile>& getProjectileVector() { return this->projectiles; }
	std::vector<Tower>& getTowerVector() { return this->towers; }
private:
	std::vector<Enemy> enemies; //List of enemies present in game instance. Works similar to an array-list hybrid
	std::vector<Projectile> projectiles; //List of projectiles in game instance.
	std::vector<Tower> towers; //List of towers in game instance.
	int mPlayerGold = 650; // Central player gold count, will update upon tower purchase or enemy defeat
	int mPlayerHealth = 150; // Player health count. Reduces if enemy reaches end, game ends if reaches zero
};