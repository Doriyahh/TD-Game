#include "Map.hpp"
#include <SFML/Graphics.hpp>

Map::Map()
{
    //Background
    background.setSize(sf::Vector2f(1200.f, 900.f));
    background.setFillColor(sf::Color::Green);

    //Paths
    paths.push_back(Path({ 200.f, 75.f }, { 0.f, 100.f }, sf::Color::Yellow));
    paths.push_back(Path({ 75.f, 600.f }, { 200.f, 100.f }, sf::Color::Yellow));
    paths.push_back(Path({ 400.f, 75.f }, { 200.f, 700.f }, sf::Color::Yellow));
    paths.push_back(Path({ 75.f, 400.f }, { 525.f, 300.f }, sf::Color::Yellow));
    paths.push_back(Path({ 200.f, 75.f }, { 400.f, 300.f }, sf::Color::Yellow));
    paths.push_back(Path({ 75.f, 300.f }, { 400.f, 50.f }, sf::Color::Yellow));
    paths.push_back(Path({ 700.f, 75.f }, { 450.f, 50.f }, sf::Color::Yellow));
    paths.push_back(Path({ 75.f, 400.f }, { 1100.f, 50.f }, sf::Color::Yellow));
    paths.push_back(Path({ 300.f, 75.f }, { 800.f, 375.f }, sf::Color::Yellow));
    paths.push_back(Path({ 75.f, 400.f }, { 800.f, 375.f }, sf::Color::Yellow));
    paths.push_back(Path({ 400.f, 75.f }, { 800.f, 775.f }, sf::Color::Yellow));

    waypoints = {
    {0.f, 137.5f},      // start
    {237.5f, 137.5f},    // right
    {237.5f, 737.5f},     // down
    {562.5f, 737.5f},     // right
    {562.5f, 337.5f},      // up
    {437.5f, 337.5f},     // right
    {437.5f, 87.5f},    // down
    {1137.5f, 87.5f},     // left
    {1137.5f, 412.5f},     // down
    {837.5f, 412.5f},
    {837.5f, 812.5f},
    {1200.f, 812.5f}
    };
}


void Map::draw(sf::RenderWindow& window)
{
    window.draw(background);
    for (auto& path : paths)
    {
        window.draw(path);
    }

    // Draw waypoint lines (FIXED VERSION)
    for (size_t i = 0; i < waypoints.size() - 1; i++)
    {
        sf::Vertex line[2];

        line[0].position = waypoints[i];
        line[0].color = sf::Color::Red;

        line[1].position = waypoints[i + 1];
        line[1].color = sf::Color::Red;

        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

}

const std::vector<sf::Vector2f>& Map::getWaypoints() const
{
        return waypoints;
}


