#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Enemy.hpp"
#include "Projectile.hpp"
#include "Game.hpp"




//PLEASE READ IF WORKING ON TOWERS!!!
/*
When instantiating a tower, please add it to the game tower vector.
This is NOT a "Vector2f" from sf, this is a C++ specific data structure, acting as an array-linked list hybrid
You do this by doing "mainGame.getTowerVector().push_back('your_tower');"
You will need access to the mainGame object wherever you want to call it, but this is necessary for keeping track of
all towers in the game state. Similarly, when a tower "dies", you will need to call
"mainGame->getTowerVector().removeTower(this)" - It will remove that object from the list, so it will not get drawn anymore.
This should not interfere with any systems you want to add to your towers, just a supplementary thing you can add to a constructor,
given you have access to the mainGame object.
A similar thing will be implemented for all temporary objects within the game.

- Brock
*/


//Base tower class to be inherited by all other tower classes.
//Origin is CENTER OF TOWER. Has range in form of circleshape object, also has origin at center.


enum class TowerType { None, Basic, Sniper, AOE };

class Tower : public sf::RectangleShape
{
public:
    Tower(Game*& game, const sf::Vector2f& pos, const float& Damage, const float& AS, const float& Range) 
		: sf::RectangleShape(sf::Vector2f(60,60)) // can change the size of the tower here if you want 
        {
        //not sure if this is how you want the constructor or not

         //Change origin to center of tower
        this->setOrigin(sf::Vector2f(30, 30));

        this->setPosition(pos);

        this->mDamage = Damage;

        this->mAS = AS;

        this->mRange = Range;

        this->mShootTimer = 0;

        this->mGame = game;

        this->setOutlineThickness(7.0f);
        this->setOutlineColor(sf::Color(255, 255, 255, 0));

        // Set up the range circle - centered on tower, radius = mRange
        mRangeCircle.setRadius(Range);
        // use the circle's own radius as a vector origin (SFML expects a Vector2f)
        mRangeCircle.setOrigin(sf::Vector2f(Range, Range));
        mRangeCircle.setPosition(this->getPosition());
        this->getRangeCircle().setFillColor(sf::Color(70, 70, 70, 130));
        mRangeCircle.setOutlineColor(sf::Color(43, 43, 43, 150)); // slightly visible outline
        mRangeCircle.setOutlineThickness(7.0f);

        }

    virtual ~Tower() {
    }

    void displayRange();

    // Called each frame to handle shooting logic - virtual so subclasses can override
    virtual void update();

    //Specific update function for tower in the process of being placed
    bool updateBuying();

    // Draws the range circle to the window (call when tower is selected or placing)
    virtual void drawRange(sf::RenderWindow& window);

    // Returns true if another tower is within the minimum placement distance
    bool isTooClose(Tower*& other);

    //Checks if the spot the tower is in is valid
    bool isPlacementValid();
    
    //setters
    void setDamage(float newDamage);

    void setAS(float newAS);

    void setRange(float newRange); // Also updates the range circle to match the new range

    //getters
    float getDamage() const;

    float getAS() const;

    float getRange() const;

    float getPrice() { return this->mPrice; }

    bool getClickedStatus() { return this->mIsClicked; }

    bool getUp1() { return this->mUpgradeOne; }

    bool getUp2() { return this->mUpgradeTwo; }

    void trueUp1() { this->mUpgradeOne = true; }

    void trueUp2() { this->mUpgradeTwo = true; }

    virtual TowerType getType() { return TowerType::None; };

    void flipClickedStatus() {
        if (this->mIsClicked) {
            this->mIsClicked = false;
        }
        else {
            this->mIsClicked = true;
        }
    }

    void draw(sf::RenderWindow& window);

    Enemy*& getTarget() { return this->mTarget; }

    void clearTarget() { this->mTarget = nullptr; }

    Game*& getGame() { return this->mGame; }

    sf::CircleShape& getRangeCircle() { return this->mRangeCircle; }

    // Minimum distance allowed between two towers on placement
    static constexpr float PLACEMENT_RADIUS = 45.0f;

protected:

    float mDamage;

    float mAS; //AS stands for attack speed (easier to write using AS. Can change if you would like to)

    float mRange; // shooting radius in pixels

	float mShootTimer; //timer for shooting, tracks time between shots

    float mPrice;

    bool mIsClicked = false;

    sf::Texture mTexture;

    sf::Texture* pTexture = &mTexture;

    Enemy* mTarget = nullptr; //Current target of tower

    Game* mGame = nullptr;

	sf::CircleShape mRangeCircle; //circle that shows the range of the tower

    bool mUpgradeOne = false;

    bool mUpgradeTwo = false;

};