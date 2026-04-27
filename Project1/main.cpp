#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "BasicTower.hpp"
#include "SniperTower.hpp"
#include "BaseEnemy.hpp"
#include "Projectile.hpp"
#include "FasterEnemy.hpp";
#include "Tank.hpp";
int main()
{
    /*sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
   sf::CircleShape shape(100.f);
   shape.setFillColor(sf::Color::Green);

   while (window.isOpen())
   {
       while (const std::optional event = window.pollEvent())
       {
           if (event->is<sf::Event::Closed>())
               window.close();
       }

       window.clear();
       window.draw(shape);
       window.display();
   }*/

    sf::RenderWindow window(sf::VideoMode({ 1200, 900 }), "Tower Defense Game");
    window.setFramerateLimit(60);

    Game* mainGame = new Game;
    Map map;
    glassesAndy tower(mainGame, sf::Vector2f(340, 400));
    CigarAndy sniper(mainGame, sf::Vector2f(1100, 800));
    BasicEnemy1* newEnemy = new BasicEnemy1(mainGame, map.getWaypoints());
    FastEnemy* Fast = new FastEnemy(mainGame, map.getWaypoints());
    TankEnemy* Tank = new TankEnemy(mainGame, map.getWaypoints());
    mainGame->getEnemyVector().push_back(newEnemy);
    mainGame->getEnemyVector().push_back(Fast);
    mainGame->getEnemyVector().push_back(Tank);
    while (window.isOpen())
    {
        window.clear();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        for (int i = 0; i < mainGame->getTowerVector().size(); i++) {
            mainGame->getTowerVector()[i]->update();
        }

        for (int i = 0; i < mainGame->getEnemyVector().size(); i++)
        {
            mainGame->getEnemyVector()[i]->update();
        }

        for (int i = 0; i < mainGame->getProjectileVector().size(); i++)
        {
            mainGame->getProjectileVector()[i]->update();
        }

        window.clear();
        map.draw(window);

        //Draws all towers in game state
        for (int i = 0; i < mainGame->getTowerVector().size(); i++) {
            window.draw(*mainGame->getTowerVector()[i]);
        }
        //Draws all enemies in game state
        for (int i = 0; i < mainGame->getEnemyVector().size(); i++) {
            window.draw(*mainGame->getEnemyVector()[i]);
        }
        //Draws all projectiles in game state
        for (int i = 0; i < mainGame->getProjectileVector().size(); i++) {
            window.draw(*mainGame->getProjectileVector()[i]);
        }
        for (int i = 0; i < mainGame->getLaserVector().size(); i++) {
            window.draw(*mainGame->getLaserVector()[i]);
        }
        window.display();
    }

    return 0;
}