#pragma once

#include "Game.hpp"
#include "Map.hpp"
#include "AoeTower.hpp"
#include "BasicTower.hpp"
#include "SniperTower.hpp"


class SideMenu : public sf::RectangleShape {
public:
	SideMenu(Game* mainGame, sf::RenderWindow& window) {
		this->setSize(sf::Vector2f(400, 900));
		this->setPosition(sf::Vector2f(1200, 0));
		this->setTexture(mMenuBackground);
		this->mGame = mainGame;
		this->mWindow = &window;

		this->mPlayerGold->setLineAlignment(sf::Text::LineAlignment::Center);
		this->mPlayerHealth->setLineAlignment(sf::Text::LineAlignment::Center);
		this->mBasicInfo->setLineAlignment(sf::Text::LineAlignment::Center);
		this->mSniperInfo->setLineAlignment(sf::Text::LineAlignment::Center);
		this->mAoeInfo->setLineAlignment(sf::Text::LineAlignment::Center);


		this->mGoldImage.setSize(sf::Vector2f(70, 70));
		this->mGoldImage.setPosition(sf::Vector2f(1230, 20));

		this->mHealthImage.setSize(sf::Vector2f(50, 50));
		this->mHealthImage.setPosition(sf::Vector2f(1240, 100));

		this->mPlayerGold->setCharacterSize(43);
		this->mPlayerGold->setPosition(sf::Vector2f(1350, 20));
		this->mPlayerGold->setFillColor(sf::Color::White);
		this->mPlayerGold->setOutlineColor(sf::Color::Black);
		this->mPlayerGold->setOutlineThickness(7.0f);

		this->mRoundDisplay->setCharacterSize(43);
		this->mRoundDisplay->setPosition(sf::Vector2f(1250, 160));
		this->mRoundDisplay->setFillColor(sf::Color::White);
		this->mRoundDisplay->setOutlineColor(sf::Color::Black);
		this->mRoundDisplay->setOutlineThickness(7.0f);

		this->mPlayerHealth->setCharacterSize(43);
		this->mPlayerHealth->setPosition(sf::Vector2f(1350, 95));
		this->mPlayerHealth->setFillColor(sf::Color::White);
		this->mPlayerHealth->setOutlineColor(sf::Color::Black);
		this->mPlayerHealth->setOutlineThickness(7.0f);

		this->mBasicInfo->setCharacterSize(33);
		this->mBasicInfo->setPosition(sf::Vector2f(1460, 320));
		this->mBasicInfo->setFillColor(sf::Color::White);
		this->mBasicInfo->setOutlineColor(sf::Color::Black);
		this->mBasicInfo->setOutlineThickness(5.0f);

		this->mSniperInfo->setCharacterSize(33);
		this->mSniperInfo->setPosition(sf::Vector2f(1460, 520));
		this->mSniperInfo->setFillColor(sf::Color::White);
		this->mSniperInfo->setOutlineColor(sf::Color::Black);
		this->mSniperInfo->setOutlineThickness(5.0f);

		this->mAoeInfo->setCharacterSize(33);
		this->mAoeInfo->setPosition(sf::Vector2f(1460, 720));
		this->mAoeInfo->setFillColor(sf::Color::White);
		this->mAoeInfo->setOutlineColor(sf::Color::Black);
		this->mAoeInfo->setOutlineThickness(5.0f);

		this->mBasicTowerImage.setSize(sf::Vector2f(100, 100));
		this->mBasicTowerImage.setOrigin(sf::Vector2f(50, 50));
		this->mBasicTowerImage.setPosition(sf::Vector2f(1275, 375));
		this->mBasicTowerImage.setRotation(sf::degrees(180));

		this->mSniperTowerImage.setSize(sf::Vector2f(100, 100));
		this->mSniperTowerImage.setOrigin(sf::Vector2f(50, 50));
		this->mSniperTowerImage.setPosition(sf::Vector2f(1275, 575));
		this->mSniperTowerImage.setRotation(sf::degrees(90));

		this->mAoeTowerImage.setSize(sf::Vector2f(100, 100));
		this->mAoeTowerImage.setOrigin(sf::Vector2f(50, 50));
		this->mAoeTowerImage.setPosition(sf::Vector2f(1275, 775));

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

	void buyBasicTower();

	void buySniperTower();

	void buyAoeTower();

	sf::Text*& getGoldText() { return this->mPlayerGold; }

	sf::Text*& getHealthText() { return this->mPlayerHealth; }

	//Will draw all components of menu
	void draw(sf::RenderWindow& window);

	//Will update all text and such
	void update();

private:
	Game* mGame;
	sf::RenderWindow* mWindow;
	//Font in use, can be anything i just used something i had downloaded
	sf::Font mFont = sf::Font(std::filesystem::path("External/Fonts/edosz.ttf"));
	sf::Texture* mMenuBackground = new sf::Texture(std::filesystem::path("External/Images/MenuBackground.png"));
	//Text elements
	std::string mHealth;
	std::string mRound;
	sf::Text* mPlayerHealth = new sf::Text(this->mFont, mHealth);
	std::string mGold;
	sf::Text* mPlayerGold = new sf::Text(this->mFont, mGold);
	sf::Text* mBasicInfo = new sf::Text(this->mFont, "Glasses Andy\nBasic Type\n125 Gold");
	sf::Text* mSniperInfo = new sf::Text(this->mFont, "Cigar Andy\nSniper Type\n350 Gold");
	sf::Text* mAoeInfo = new sf::Text(this->mFont, "Good Guy Andy\nAoE Type\n225 Gold");
	sf::Text* mRoundDisplay = new sf::Text(this->mFont, this->mRound);
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

	//Tower in process of being bought
	Tower* mTower = nullptr;
};