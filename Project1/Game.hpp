#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Projectile;
class Enemy;
class Tower;

// Primary class for player values. May also end up containing game wrapper.
//Also contains lists for all temporary objects within the game for easy access when needed
class Game {
public:
	Game() = default;
	Game(sf::RenderWindow& window) { 
		this->mWindow = &window;
		//Skip header
		std::getline(*this->mRoundStream, this->mRoundString);

		this->mStartRoundText->setLineAlignment(sf::Text::LineAlignment::Center);
		this->mStartRoundText->setCharacterSize(30);
		this->mStartRoundText->setPosition(sf::Vector2f(600, 860));
		this->mStartRoundText->setFillColor(sf::Color::White);
		this->mStartRoundText->setOutlineThickness(7.0f);
		this->mStartRoundText->setOutlineColor(sf::Color::Black);
	}
	int getGold(void) { return this->mPlayerGold; }
	int getHealth(void) { return this->mPlayerHealth; }
	void setGold(int input) { this->mPlayerGold = input; }
	void setHealth(int input) { this->mPlayerHealth = input; }
	void setMousePos(sf::Vector2f pos) { this->mousePos = pos; }
	Enemy*& getEnemy() { return this->newEnemy; }
	int& getSpawnTimer() { return this->mSpawnTimer; }
	void incSpawnTimer() { this->mSpawnTimer--; }
	bool getStopSpawn() { return this->stopSpawn; }
	void setStopSpawn(bool set) { this->stopSpawn = set; }
	sf::Text*& getRoundText() { return this->mStartRoundText; }
	int getRound() { return this->mRound; }
	sf::RenderWindow*& getWindow() { return this->mWindow; }
	sf::Vector2f& getMousePos() { return this->mousePos; }
	void roundHandler();
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
	std::ifstream* mRoundStream = new std::ifstream("Rounds.csv");
	std::string mRoundString;
	std::stringstream mRoundStringStream;
	int mSpawnTimer = 1000;
	int mRound = 0;
	Enemy* newEnemy = nullptr;
	bool stopSpawn = true;
	Map mGameMap;
	int mPlayerGold = 650; // Central player gold count, will update upon tower purchase or enemy defeat
	int mPlayerHealth = 150; // Player health count. Reduces if enemy reaches end, game ends if reaches zero
	sf::RenderWindow* mWindow = nullptr;
	sf::Vector2f mousePos;

	sf::Font mFont = sf::Font(std::filesystem::path("External/Fonts/edosz.ttf"));
	sf::Text* mStartRoundText = new sf::Text(this->mFont, "Press Space to Start Round");
};