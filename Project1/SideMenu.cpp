#include "SideMenu.hpp"


void SideMenu::buyBasicTower()
{
	sf::Vector2f mousePosWorld = this->mWindow->mapPixelToCoords(sf::Mouse::getPosition());
	if (this->mBasicTowerImage.getGlobalBounds().contains(mousePosWorld) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->mTower == nullptr) {
		glassesAndy* newTower = new glassesAndy(this->getGame(), mousePosWorld);
		this->mTower = newTower;
	}
}

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

	//Draw tower being placed
	if (this->mTower != nullptr) {
		this->getGame()->getWindow()->draw(*mTower);
	}
}

void SideMenu::update()
{
	//Updates counters and text
	this->mGold = std::to_string(this->mGame->getGold());
	this->mHealth = std::to_string(this->mGame->getHealth());
	this->mPlayerHealth->setString(this->mHealth);
	this->mPlayerGold->setString(this->mGold);

	

	if (this->mTower != nullptr) {
		if (this->mTower->updateBuying()) {
			this->mTower = nullptr;
		}
	}
	else {
		this->buyBasicTower();
	}
}
