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

	//Draw upgrade menu
	if (this->mCheckClicked) {
		window.draw(this->mUpgradeBackground);
		window.draw(this->mUpgradeTowerImage1);
		window.draw(this->mUpgradeTowerImage2);
		

		switch (this->mClickedTower->getType()) {
		case TowerType::Basic:
			if (!this->mClickedTower->getUp1()) {
				window.draw(*this->mBasicUpInfo1);
			}
			else {
				window.draw(*this->mBought1);
			}
			if (!this->mClickedTower->getUp2()) {
				window.draw(*this->mBasicUpInfo2);
			}
			else {
				window.draw(*this->mBought2);
			}
			break;
		case TowerType::Sniper:
			if (!this->mClickedTower->getUp1()) {
				window.draw(*this->mSniperUpInfo1);
			}
			else {
				window.draw(*this->mBought1);
			}
			if (!this->mClickedTower->getUp2()) {
				window.draw(*this->mSniperUpInfo2);
			}
			else {
				window.draw(*this->mBought2);
			}
			break;
		case TowerType::AOE:
			if (!this->mClickedTower->getUp1()) {
				window.draw(*this->mAoeUpInfo1);
			}
			else {
				window.draw(*this->mBought1);
			}
			if (!this->mClickedTower->getUp2()) {
				window.draw(*this->mAoeUpInfo2);
			}
			else {
				window.draw(*this->mBought2);
			}
			break;
		}
	}
}

void SideMenu::update()
{
	this->mCheckClicked = false;
	//Updates counters and text
	this->mGold = std::to_string(this->mGame->getGold());
	this->mHealth = std::to_string(this->mGame->getHealth());
	this->mPlayerHealth->setString(this->mHealth);
	this->mPlayerGold->setString(this->mGold);
	

	
	for (int i = 0; i < this->getGame()->getTowerVector().size(); i++) {
		if (this->getGame()->getTowerVector()[i]->getClickedStatus()) {
			this->mCheckClicked = true;
			this->mClickedTower = this->getGame()->getTowerVector()[i];
		}
	}
	if (!this->mCheckClicked) {
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
	else {
		switch (this->mClickedTower->getType()) {
		case TowerType::Basic:
			if (this->mUpgradeTowerImage1.getGlobalBounds().contains(this->getGame()->getMousePos()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !this->mClickedTower->getUp1() && this->getGame()->getGold() >= 225) {
				this->mClickedTower->trueUp1();
				this->getGame()->setGold(this->getGame()->getGold() - 225);
			} else if (this->mUpgradeTowerImage2.getGlobalBounds().contains(this->getGame()->getMousePos()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !this->mClickedTower->getUp2() && this->getGame()->getGold() >= 175) {
				this->mClickedTower->trueUp2();
				this->getGame()->setGold(this->getGame()->getGold() - 175);
			}
			break;
		case TowerType::Sniper:
			if (this->mUpgradeTowerImage1.getGlobalBounds().contains(this->getGame()->getMousePos()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !this->mClickedTower->getUp1() && this->getGame()->getGold() >= 500) {
				this->mClickedTower->trueUp1();
				this->getGame()->setGold(this->getGame()->getGold() - 500);
			}
			else if (this->mUpgradeTowerImage2.getGlobalBounds().contains(this->getGame()->getMousePos()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !this->mClickedTower->getUp2() && this->getGame()->getGold() >= 300) {
				this->mClickedTower->trueUp2();
				this->getGame()->setGold(this->getGame()->getGold() - 300);
			}
			break;
		case TowerType::AOE:
			if (this->mUpgradeTowerImage1.getGlobalBounds().contains(this->getGame()->getMousePos()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !this->mClickedTower->getUp1() && this->getGame()->getGold() >= 225) {
				this->mClickedTower->trueUp1();
				this->getGame()->setGold(this->getGame()->getGold() - 225);
			}
			else if (this->mUpgradeTowerImage2.getGlobalBounds().contains(this->getGame()->getMousePos()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !this->mClickedTower->getUp2() && this->getGame()->getGold() >= 250) {
				this->mClickedTower->trueUp2();
				this->getGame()->setGold(this->getGame()->getGold() - 250);
			}
			break;
		}
	}
}
