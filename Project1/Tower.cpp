#include "Tower.hpp"

void Tower::update()
{
    // Base update just ticks the shoot timer down
    // Subclasses will override this to actually shoot
    if (mShootTimer > 0.0f)
    {
        mShootTimer--;
    }
}

//Update that specifically runs while tower is being bought
bool Tower::updateBuying()
{
    //Checks if player is still "dragging"
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        //Sets object to mouse position if so
        this->setPosition(this->getGame()->getMousePos());
        return false;
    }
    else {
        //If player is done dragging, checks if placement is valid, THEN adds tower to main
        //object list so it can start attacking
        if (this->isPlacementValid() && this->getGame()->getGold() >= this->getPrice()) {
            this->getGame()->getTowerVector().push_back(this);
            this->getGame()->setGold(this->getGame()->getGold() - this->getPrice());
            this->getRangeCircle().setPosition(this->getPosition());
            return true;
        }
        //Does not add tower to object list if placement is invalid.
        return true;
    }
}

void Tower::drawRange(sf::RenderWindow& window)
{
    window.draw(mRangeCircle);
}



bool Tower::isTooClose(Tower*& other)
{
    if (this == other) {
        return false;
    }

    // Get distance between this tower and another
    if (this->getGlobalBounds().findIntersection(other->getGlobalBounds())) {
        return true;
    }
    else {
        return false;
    }
}

bool Tower::isPlacementValid()
{
    //Checks all collisions with other towers
   for (int i = 0; i < this->getGame()->getTowerVector().size(); i++) {
        if (this->isTooClose(this->getGame()->getTowerVector()[i])) {
            this->setFillColor(sf::Color(200, 0, 0, 255));
            return false;
        }
    }
    //Checks collisions with paths
    for (int i = 0; i < this->getGame()->getMap().getPaths().size(); i++) {
        if (this->getGlobalBounds().findIntersection(this->getGame()->getMap().getPaths()[i].getGlobalBounds())) {
            this->setFillColor(sf::Color(200, 0, 0, 255));
            return false;
        }
    }
    //Checks if within map border
    if (this->getGlobalBounds().findIntersection(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(1200.f, 900.f)))) {
        this->setFillColor(sf::Color(255, 255, 255, 255));
        return true;
    }
    else {
        this->setFillColor(sf::Color(200, 0, 0, 255));
        return false;
    }
    
}

void Tower::setDamage(float newDamage)
{
    this->mDamage = newDamage;
}

void Tower::setAS(float newAS)
{
    this->mAS = newAS;
}

void Tower::setRange(float newRange)
{
    this->mRange = newRange;

    // Keep range circle in sync when range is updated
    mRangeCircle.setRadius(newRange);
    mRangeCircle.setOrigin(sf::Vector2f(newRange, newRange));
}

float Tower::getDamage() const
{
    return this->mDamage;
}

float Tower::getAS() const
{
    return this->mAS;
}

float Tower::getRange() const
{
    return this->mRange;
}