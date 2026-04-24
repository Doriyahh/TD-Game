#include "Tower.hpp"

void Tower::update(float dt)
{
    // Base update just ticks the shoot timer down
    // Subclasses will override this to actually shoot
    if (mShootTimer > 0.0f)
    {
        mShootTimer -= dt;
    }
}

void Tower::drawRange(sf::RenderWindow& window)
{
    window.draw(mRangeCircle);
}

bool Tower::isTooClose(const Tower& other) const
{
    // Get distance between this tower and another
    sf::Vector2f diff = this->getPosition() - other.getPosition();
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    return distance < PLACEMENT_RADIUS;
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