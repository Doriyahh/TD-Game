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

bool Tower::updateBuying()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        this->setPosition(this->getGame()->getMousePos());
        return false;
    }
    else {
        if (this->isPlacementValid() && this->getGame()->getGold() >= this->getPrice()) {
            this->getGame()->getTowerVector().push_back(this);
            this->getGame()->setGold(this->getGame()->getGold() - this->getPrice());
            return true;
        }
        return false;
    }
}

void Tower::drawRange(sf::RenderWindow& window)
{
    window.draw(mRangeCircle);
}



bool Tower::isTooClose(Tower*& other)
{
    // Get distance between this tower and another
    sf::Vector2f diff = this->getPosition() - other->getPosition();
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    return distance > PLACEMENT_RADIUS;
}

bool Tower::isPlacementValid()
{
    //Checks all collisions with other towers
    for (int i = 0; i < this->getGame()->getTowerVector().size(); i++) {
        if (this->isTooClose(this->getGame()->getTowerVector()[i])) {
            this->setFillColor(sf::Color(255, 0, 0, 200));
            return false;
        }
    }
    //Checks collisions with paths
    for (int i = 0; i < this->getGame()->getMap().getPaths().size(); i++) {
        if (this->getGlobalBounds().findIntersection(this->getGame()->getMap().getPaths()[i].getGlobalBounds())) {
            return false;
        }
    }
    //Checks if within map border
    if (this->getGlobalBounds().findIntersection(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(1200.f, 900.f)))) {
        return true;
    }
    else {
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

sf::CircleShape Tower::getRangeCircle() const
{
    return this->mRangeCircle;
}