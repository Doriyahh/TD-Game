#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class Tower : public sf::RectangleShape
{
public:
    Tower(const sf::Vector2f& pos, const float& Damage = 0.0f, const float& AS = 0.0f, const float& Range = 0.0f, const float& ShootTimer = 0.0f) 
		: sf::RectangleShape(sf::Vector2f(50, 80)) // can change the size of the tower here if you want 
        {
        //not sure if this is how you want the constructor or not

        this->setPosition(pos);

        this->mDamage = Damage;

        this->mAS = AS;

        this->mRange = Range;

        this->mShootTimer = ShootTimer;

        // Set up the range circle - centered on tower, radius = mRange
        mRangeCircle.setRadius(Range);
        // use the circle's own radius as a vector origin (SFML expects a Vector2f)
        mRangeCircle.setOrigin(sf::Vector2f(Range, Range));
        mRangeCircle.setPosition(pos);
        mRangeCircle.setFillColor(sf::Color(100, 100, 255, 50));   // transparent blue fill
        mRangeCircle.setOutlineColor(sf::Color(100, 100, 255, 150)); // slightly visible outline
        mRangeCircle.setOutlineThickness(1.0f);

        }

    // Called each frame to handle shooting logic - virtual so subclasses can override
    virtual void update(float dt);

    // Draws the range circle to the window (call when tower is selected or placing)
    virtual void drawRange(sf::RenderWindow& window);

    // Returns true if another tower is within the minimum placement distance
    bool isTooClose(const Tower& other) const;
    
    //setters
    void setDamage(float newDamage);

    void setAS(float newAS);

    void setRange(float newRange); // Also updates the range circle to match the new range

    //getters
    float getDamage() const;

    float getAS() const;

    float getRange() const;

    sf::CircleShape getRangeCircle() const;

    // Minimum distance allowed between two towers on placement
    static constexpr float PLACEMENT_RADIUS = 60.0f;

protected:

    float mDamage;

    float mAS; //AS stands for attack speed (easier to write using AS. Can change if you would like to)

    float mRange; // shooting radius in pixels

	float mShootTimer; //timer for shooting, tracks time between shots

	sf::CircleShape mRangeCircle; //circle that shows the range of the tower

};