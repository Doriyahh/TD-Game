#pragma once
#include <SFML/Graphics.hpp>
#include "SideMenu.hpp"
#include "Game.hpp"

class EndScreen : public sf::RectangleShape
{
public:
	EndScreen(sf::RenderWindow& window, Game* mainGame) {
		this->mGame = mainGame;
		this->setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
		this->setPosition(sf::Vector2f(0, 0));
		this->setTexture(this->mBackground);


		this->mLost->setCharacterSize(80);
		this->mLost->setLineAlignment(sf::Text::LineAlignment::Center);
		this->mLost->setPosition(sf::Vector2f(window.getSize().x / 2, 350));
		this->mLost->setFillColor(sf::Color::White);
		this->mLost->setOutlineThickness(10.0f);
		this->mLost->setOutlineColor(sf::Color::Black);

		this->mWon->setCharacterSize(80);
		this->mWon->setLineAlignment(sf::Text::LineAlignment::Center);
		this->mWon->setPosition(sf::Vector2f(window.getSize().x / 2, 350));
		this->mWon->setFillColor(sf::Color::White);
		this->mWon->setOutlineThickness(10.0f);
		this->mWon->setOutlineColor(sf::Color::Black);
	}

	void drawLost(sf::RenderWindow& window) {
		window.draw(*this);
		window.draw(*this->mLost);

		//input whatever photo you want here for the losing screen
	}

	void drawWon(sf::RenderWindow& window) {
		
		window.draw(*this);
		window.draw(*this->mWon);
		//input whatever photo you want here for the winning screen
	}
	bool isWin()
	{
		return this->mGame->getRound() > 10;
		this->mGame->getEnemyVector().empty();
	}

	bool isLost()
	{
		return this->mGame->getHealth() <= 0;
	}

	bool GameOver()
	{
		return isWin() || isLost();
	}

	void drawWindow(sf::RenderWindow& window)
	{
		if (isLost())
		{
			drawLost(window);
		
			//logic for enscreen goes here
		}
		else if (isWin()) //check to see the rounds 
		{
			drawWon(window);
		}
	}
private:
	Game* mGame = nullptr;
	sf::Font mFont = sf::Font(std::filesystem::path("External/Fonts/edosz.ttf"));
	sf::Texture* mBackground = new sf::Texture(std::filesystem::path("External/Images/SkydiveAndy.png")); //make this background the picture you want

	sf::Text* mLost = new sf::Text(this->mFont, "You Lost"); 
	sf::Text* mWon = new sf::Text(this->mFont, "You Won!");
};