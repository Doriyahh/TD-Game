#pragma once

#include "Game.hpp"
#include "Map.hpp"
#include "AoeTower.hpp"
#include "BasicTower.hpp"
#include "SniperTower.hpp"


class SideMenu : public sf::RectangleShape {
public:
	SideMenu(Game* mainGame) {
		this->setSize(sf::Vector2f(400, 900));
		this->setPosition(sf::Vector2f(1200, 0));
		this->setFillColor(sf::Color(117, 71, 33));
		this->mGame = mainGame;

		this->mGoldImage.setSize(sf::Vector2f(70, 70));
		this->mGoldImage.setPosition(sf::Vector2f(1230, 20));

		this->mHealthImage.setSize(sf::Vector2f(50, 50));
		this->mHealthImage.setPosition(sf::Vector2f(1240, 100));

		this->mPlayerGold->setCharacterSize(43);
		this->mPlayerGold->setFont(this->mFont);
		this->mPlayerGold->setPosition(sf::Vector2f(1350, 20));
		this->mPlayerGold->setFillColor(sf::Color::White);
		this->mPlayerGold->setOutlineColor(sf::Color::Black);
		this->mPlayerGold->setOutlineThickness(7.0f);

		this->mPlayerHealth->setCharacterSize(43);
		this->mPlayerHealth->setFont(this->mFont);
		this->mPlayerHealth->setPosition(sf::Vector2f(1350, 95));
		this->mPlayerHealth->setFillColor(sf::Color::White);
		this->mPlayerHealth->setOutlineColor(sf::Color::Black);
		this->mPlayerHealth->setOutlineThickness(7.0f);

		this->mBasicTowerImage.setSize(sf::Vector2f(150, 150));
		this->mBasicTowerImage.setOrigin(sf::Vector2f(75, 75));
		this->mBasicTowerImage.setPosition(sf::Vector2f(1400, 275));
		this->mBasicTowerImage.setRotation(sf::degrees(180));

		this->mSniperTowerImage.setSize(sf::Vector2f(150, 150));
		this->mSniperTowerImage.setOrigin(sf::Vector2f(75, 75));
		this->mSniperTowerImage.setPosition(sf::Vector2f(1400, 475));
		this->mSniperTowerImage.setRotation(sf::degrees(90));

		this->mAoeTowerImage.setSize(sf::Vector2f(150, 150));
		this->mAoeTowerImage.setOrigin(sf::Vector2f(75, 75));
		this->mAoeTowerImage.setPosition(sf::Vector2f(1400, 675));

		this->mGoldImage.setTexture(this->mGoldTexture);
		this->mHealthImage.setTexture(this->mHealthTexture);
		this->mBasicTowerImage.setTexture(this->mBasicTexture);
		this->mSniperTowerImage.setTexture(this->mSniperTexture);
		this->mAoeTowerImage.setTexture(this->mAoeTexture);
	}

	Game*& getGame() { return this->mGame; }

	sf::Font& getFont() { return this->mFont; }

	void setHealthString(std::string health) { this->mHealth = health; }

	void setHealthText(sf::Text*& health) { this->mPlayerHealth = health; }

	void setGoldString(std::string& gold) { this->mGold = gold; }

	void setGoldText(sf::Text*& gold) { this->mPlayerGold = gold; }

	sf::Text*& getGoldText() { return this->mPlayerGold; }

	sf::Text*& getHealthText() { return this->mPlayerHealth; }

	//Will draw all components of menu
	void draw(sf::RenderWindow& window);

	//Will update all text and such
	void update();

private:
	Game* mGame;
	//Font in use, can be anything i just used something i had downloaded
	sf::Font mFont = sf::Font(std::filesystem::path("External/Fonts/edosz.ttf"));
	//Text elements
	std::string mHealth;
	sf::Text* mPlayerHealth = new sf::Text(this->mFont, mHealth);
	std::string mGold;
	sf::Text* mPlayerGold = new sf::Text(this->mFont, mGold);
	//All visual elements that isnt the menu background and text
	sf::RectangleShape mGoldImage;
	sf::RectangleShape mHealthImage;
	sf::RectangleShape mBasicTowerImage;
	sf::RectangleShape mSniperTowerImage;
	sf::RectangleShape mAoeTowerImage;
	//Paths to all images used
	sf::Texture* mGoldTexture = new sf::Texture(std::filesystem::path("External/Images/Gold.png"));
	sf::Texture* mHealthTexture = new sf::Texture(std::filesystem::path("External/Images/Heart.png"));
	sf::Texture* mBasicTexture = new sf::Texture(std::filesystem::path("External/Images/GlassesAndy.png"));
	sf::Texture* mSniperTexture = new sf::Texture(std::filesystem::path("External/Images/CigarAndy.png"));
	sf::Texture* mAoeTexture = new sf::Texture(std::filesystem::path("External/Images/GoodBoyAndy.png"));
};