#include "SideMenu.hpp"

void SideMenu::draw(sf::RenderWindow& window)
{
	//Draws all menu elements and does necessary updates
	this->update();

	//Background draw
	window.draw(*this);

	//Text draws
	window.draw(*this->mPlayerGold);
	window.draw(*this->mPlayerHealth);
	window.draw(*this->mBasicInfo);
	window.draw(*this->mSniperInfo);
	window.draw(*this->mAoeInfo);

	//Image draws
	window.draw(this->mGoldImage);
	window.draw(this->mHealthImage);
	window.draw(this->mBasicTowerImage);
	window.draw(this->mSniperTowerImage);
	window.draw(this->mAoeTowerImage);
}

void SideMenu::update()
{
	//Updates counters and text
	this->mGold = std::to_string(this->mGame->getGold());
	this->mHealth = std::to_string(this->mGame->getHealth());
	this->mPlayerHealth->setString(this->mHealth);
	this->mPlayerGold->setString(this->mGold);
}
