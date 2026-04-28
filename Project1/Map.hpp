
#pragma once

#include <SFML/Graphics.hpp>
#include "Path.hpp"
#include <vector>

class Map : public sf::RectangleShape
{
public:
    Map();
    void draw(sf::RenderWindow& window);

    std::vector<Path>& getPaths() { return this->paths; }

    // So you guys can access the waypoints from outside the class and use them for enemy movement
    const std::vector<sf::Vector2f>& getWaypoints() const;

private:
    // Base layer
    sf::RectangleShape background;

    // Path and waypoints (unchanged)
    std::vector<Path> paths;
    std::vector<sf::Vector2f> waypoints;

    // Decoration layers (drawn back to front)
    std::vector<sf::RectangleShape> darkGrassPatches;
    std::vector<sf::RectangleShape> treeTrunks;
    std::vector<sf::CircleShape>    treeTops;
    std::vector<sf::RectangleShape> houseWalls;
    std::vector<sf::RectangleShape> houseDoors;
    std::vector<sf::RectangleShape> houseWindows;
    std::vector<sf::ConvexShape>    houseRoofs;

    // Bryan Hall clock tower building (drawn after regular houses)
    std::vector<sf::RectangleShape> ctBrick;      // crimson brick sections
    std::vector<sf::ConvexShape>    ctRoofs;       // gray hip roofs + tower cap
    std::vector<sf::RectangleShape> ctTrim;        // white cornice strips
    std::vector<sf::RectangleShape> ctWindows;     // windows
    std::vector<sf::RectangleShape> ctDoors;       // entrance door
    std::vector<sf::ConvexShape>    ctPortico;     // entrance pediment
    std::vector<sf::CircleShape>    ctClockFace;   // clock circle on tower
	std::vector<sf::RectangleShape> ctHands;       // clock hands
    std::vector<sf::RectangleShape> ttWalls;
    std::vector<sf::RectangleShape> ttWindows;
    std::vector<sf::RectangleShape> ttTrim;
    std::vector<sf::RectangleShape> ttBase;

    // Helpers
    void addTree(float x, float y);
    void addHouse(float x, float y, sf::Color wallColor = sf::Color(210, 195, 175));
    void addGrassPatch(float x, float y, float w, float h);
    void addClockTower(float x, float y); // x,y = top-left of main building body
    void generateGrassDetail(); // scatters hundreds of tiny grass slivers
    void addTallTower(float x, float y);
	void addSchrub(float x, float y);
};