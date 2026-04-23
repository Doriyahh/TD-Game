#pragma once

#include <SFML/Graphics.hpp>

class Tower : public sf::RectangleShape
{
public:
    Tower(const sf::Vector2f& pos, const float& Damage = 0.0, const float& AS = 0.0, const float& Range = 0.0) 
        : sf::RectangleShape(sf::Vector2f(50, 80))
    {
        //not sure if this is how you want the constructor or not

        this->setPosition(pos);

        this->mDamage = Damage;

        this->mAS = AS;

        this->mRange = Range;
    }


    //setters
    void setDamage(float newDamage);

    void setAS(float newAS);

    void setRange(float newRange);

    //getters
    float getDamage();

    float getAS();

    float getRange();

protected:

    float mDamage;

    float mAS; //AS stands for attack speed (easier to write using AS. Can change if you would like to)

    float mRange;
    
    //size of the tower, can be used to change the size of the tower in the future if needed


};