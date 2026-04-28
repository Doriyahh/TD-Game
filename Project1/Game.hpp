#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Tower;
class Enemy;
class Projectile;

// Primary class for player values. May also end up containing game wrapper.
//Also contains lists for all temporary objects within the game for easy access when needed
class Game {
public:
	Game() = default;
	Game(sf::RenderWindow& window) { this->mWindow = &window; }
	int getGold(void) { return this->mPlayerGold; }
	int getHealth(void) { return this->mPlayerHealth; }
	void setGold(int input) { this->mPlayerGold = input; }
	void setHealth(int input) { this->mPlayerHealth = input; }
	void setMousePos(sf::Vector2f pos) { this->mousePos = pos; }
	sf::RenderWindow*& getWindow() { return this->mWindow; }
	sf::Vector2f& getMousePos() { return this->mousePos; }
	Map& getMap() { return this->mGameMap; }
	void removeEnemy(Enemy* target);
	void removeTower(Tower* target);
	void removeProjectile(Projectile* target);
	void removeLaser(sf::RectangleShape* target);
	std::vector<Enemy*>& getEnemyVector() { return this->enemies; }
	std::vector<Projectile*>& getProjectileVector() { return this->projectiles; }
	std::vector<Tower*>& getTowerVector() { return this->towers; }
	std::vector<sf::RectangleShape*>& getLaserVector() { return this->lasers; }
private:
	std::vector<Enemy*> enemies; //List of enemies present in game instance. Works similar to an array-list hybrid
	std::vector<Projectile*> projectiles; //List of projectiles in game instance.
	std::vector<Tower*> towers; //List of towers in game instance.
	std::vector<sf::RectangleShape*> lasers;
	Map mGameMap;
	int mPlayerGold = 650; // Central player gold count, will update upon tower purchase or enemy defeat
	int mPlayerHealth = 150; // Player health count. Reduces if enemy reaches end, game ends if reaches zero
	sf::RenderWindow* mWindow = nullptr;
	sf::Vector2f mousePos;
};