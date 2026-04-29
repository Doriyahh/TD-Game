#include "SideMenu.hpp"
#include <iostream>

//These functions check if player has clicked any of the tower images on the menu, and begins
//purchase loops if so. Does individually for all towers
void SideMenu::buyBasicTower()
{
	if (this->mBasicTowerImage.getGlobalBounds().contains(this->getGame()->getMousePos()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->mTower == nullptr) {
		glassesAndy* newTower = new glassesAndy(this->getGame(), this->getGame()->getMousePos());
		this->mTower = newTower;
	}
}

void SideMenu::buySniperTower()
{
	if (this->mSniperTowerImage.getGlobalBounds().contains(this->getGame()->getMousePos()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->mTower == nullptr) {
		CigarAndy* newTower = new CigarAndy(this->getGame(), this->getGame()->getMousePos());
		this->mTower = newTower;
	}
}

void SideMenu::buyAoeTower()
{
	if (this->mAoeTowerImage.getGlobalBounds().contains(this->getGame()->getMousePos()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->mTower == nullptr) {
		GoodBoyAndy* newTower = new GoodBoyAndy(this->getGame(), this->getGame()->getMousePos());
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
	window.draw(*this->mRoundDisplay);

	//Image draws
	window.draw(this->mGoldImage);
	window.draw(this->mHealthImage);
	window.draw(this->mBasicTowerImage);
	window.draw(this->mSniperTowerImage);
	window.draw(this->mAoeTowerImage);

	//Draw tower being dragged
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
	this->mRound = "Round: ";
	this->mRound.append(std::to_string(this->getGame()->getRound()));
	this->mRoundDisplay->setString(this->mRound);

	
	//Checks if there is currently a tower being placed
	if (this->mTower != nullptr) {
		//Checks valid placement for color if invalid
		this->mTower->isPlacementValid();
		//Checks if the tower has been placed. If it has, removes pointer from side menu
		//to exit buying phase
		if (this->mTower->updateBuying()) {
			this->mTower = nullptr;
		}
	}
	//If there is not a tower being bought, checks if player clicked to initiate purchase
	else {
		this->buyBasicTower();
		this->buySniperTower();
		this->buyAoeTower();
	}
}
