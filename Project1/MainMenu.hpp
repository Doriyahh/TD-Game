#pragma once
#include <SFML/Graphics.hpp>

class MainMenu : public sf::RectangleShape {
public:
	MainMenu(sf::RenderWindow& window) {
		this->setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
		this->setPosition(sf::Vector2f(0, 0));
		this->setTexture(this->mBackground);

		this->mTitle->setCharacterSize(80);
		this->mTitle->setLineAlignment(sf::Text::LineAlignment::Center);
		this->mTitle->setPosition(sf::Vector2f(window.getSize().x / 2, 350));
		this->mTitle->setFillColor(sf::Color::White);
		this->mTitle->setOutlineThickness(10.0f);
		this->mTitle->setOutlineColor(sf::Color::Black);

		this->mEnterText->setCharacterSize(40);
		this->mEnterText->setLineAlignment(sf::Text::LineAlignment::Center);
		this->mEnterText->setPosition(sf::Vector2f(window.getSize().x / 2, 450));
		this->mEnterText->setFillColor(sf::Color::White);
		this->mEnterText->setOutlineThickness(5.0f);
		this->mEnterText->setOutlineColor(sf::Color::Black);

		this->helmetAndy.setSize(sf::Vector2f(200, 200));
		this->helmetAndy.setOrigin(sf::Vector2f(100, 100));
		this->helmetAndy.setPosition(sf::Vector2f(150, 750));
		this->helmetAndy.setTexture(this->mHelmetAndy);

		this->Andy2014.setSize(sf::Vector2f(200, 200));
		this->Andy2014.setOrigin(sf::Vector2f(100, 100));
		this->Andy2014.setPosition(sf::Vector2f(1450, 750));
		this->Andy2014.setTexture(this->m2014Andy);
	}

	void draw(sf::RenderWindow& window) {
		this->helmetAndy.setRotation(sf::degrees(this->helmetAndy.getRotation().asDegrees() + 2));
		this->Andy2014.setRotation(sf::degrees(this->Andy2014.getRotation().asDegrees() - 2));


		window.draw(*this);
		window.draw(*this->mTitle);
		window.draw(*this->mEnterText);
		window.draw(this->helmetAndy);
		window.draw(this->Andy2014);
	}
private:
	sf::Font mFont = sf::Font(std::filesystem::path("External/Fonts/edosz.ttf"));
	sf::Texture* mBackground = new sf::Texture(std::filesystem::path("External/Images/SkydiveAndy.png"));
	sf::Texture* mHelmetAndy = new sf::Texture(std::filesystem::path("External/Images/HelmetAndy.png"));
	sf::Texture* m2014Andy = new sf::Texture(std::filesystem::path("External/Images/2014Andy.png"));

	sf::Text* mTitle = new sf::Text(this->mFont, "Andy Tower Defense");
	sf::Text* mEnterText = new sf::Text(this->mFont, "Press Enter to Start...");

	sf::RectangleShape helmetAndy;
	sf::RectangleShape Andy2014;
};