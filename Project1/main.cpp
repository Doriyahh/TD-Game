#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "BasicTower.hpp"
#include "SniperTower.hpp"
#include "AoeTower.hpp"
#include "BaseEnemy.hpp"
#include "Projectile.hpp"
#include "FasterEnemy.hpp"
#include "Tank.hpp"
#include "Boss.hpp"
#include "HealerEnemy.hpp"
#include "SideMenu.hpp"
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

    sf::RenderWindow window(sf::VideoMode({ 1600, 900 }), "Tower Defense Game");
    window.setFramerateLimit(60);

    Game* mainGame = new Game(window);
    SideMenu sideMenu(mainGame, window);
    glassesAndy tower(mainGame, sf::Vector2f(340, 400));
    mainGame->getTowerVector().push_back(&tower);
    GoodBoyAndy aoe(mainGame, sf::Vector2f(340, 650));
    CigarAndy sniper(mainGame, sf::Vector2f(1100, 500));
    BasicEnemy1* newEnemy = new BasicEnemy1(mainGame, mainGame->getMap().getWaypoints());
    HealerEnemy* Healer = new HealerEnemy(mainGame, mainGame->getMap().getWaypoints());
    FastEnemy* Fast = new FastEnemy(mainGame, mainGame->getMap().getWaypoints());
    TankEnemy* Tank = new TankEnemy(mainGame, mainGame->getMap().getWaypoints());
    BossEnemy* Boss = new BossEnemy(mainGame, mainGame->getMap().getWaypoints());
    mainGame->getEnemyVector().push_back(newEnemy);
    mainGame->getEnemyVector().push_back(Fast);
    mainGame->getEnemyVector().push_back(Tank);
    mainGame->getEnemyVector().push_back(Boss);
    mainGame->getEnemyVector().push_back(Healer);
    while (window.isOpen())
    {
        mainGame->setMousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
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

            if (mainGame->getEnemyVector()[i]->reachedEnd())
            {
                //reduces player health
                mainGame->setHealth(mainGame->getHealth() - (int)mainGame->getEnemyVector()[i]->getDamage());

                //get rid of enemy from map
                mainGame->removeEnemy(mainGame->getEnemyVector()[i]);
                i--;


                if (Healer != nullptr)
                {
                    Healer->HealNearby(mainGame->getEnemyVector());
                }
            }
        }

        for (int i = 0; i < mainGame->getProjectileVector().size(); i++)
        {
            mainGame->getProjectileVector()[i]->update();
        }

   

        window.clear();
        mainGame->getMap().draw(window);
        

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
        
        
        //Displays side menu
        sideMenu.update();
        sideMenu.draw(window);

        window.display();
    }

    return 0;
}