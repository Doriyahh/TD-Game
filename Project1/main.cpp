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
#include "MainMenu.hpp"
int main()
{

    sf::RenderWindow window(sf::VideoMode({ 1600, 900 }), "Tower Defense Game");
    window.setFramerateLimit(60);

    Game* mainGame = new Game(window);
    mainGame->roundHandler();
    MainMenu mainMenu(window);
    bool gameStart = false;
    SideMenu sideMenu(mainGame, window);
    

    //Main menu loop
    while (window.isOpen() && gameStart == false) {
        window.clear();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        mainMenu.draw(window);
        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            gameStart = true;
        }
    }

    //Game loop
    while (window.isOpen())
    {

        mainGame->setMousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        window.clear();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    // Tell the towers to check for selection
                    for (auto& tower : mainGame->getTowerVector()) {
                        tower->displayRange();
                    }
                }
            }
        }

        std::sort(mainGame->getEnemyVector().begin(),
            mainGame->getEnemyVector().end(), [](Enemy* a, Enemy* b)
            {
                return a->getCurrentWaypoint() > b->getCurrentWaypoint();

            });

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
            }
        }

        for (int i = 0; i < mainGame->getProjectileVector().size(); i++)
        {
            mainGame->getProjectileVector()[i]->update();
        }


        //Increment the spawn timer
        mainGame->incSpawnTimer();         

        //If the spawn timer is zero and the check for round end is false
        if (mainGame->getSpawnTimer() <= 0 && mainGame->getStopSpawn() == false) {
            //Spawn new enemy
            mainGame->getEnemyVector().push_back(mainGame->getEnemy());
            //Get next enemy
            mainGame->roundHandler();           
        }
   

        window.clear();
        mainGame->getMap().draw(window);
        

        //Draws all towers in game state
        for (int i = 0; i < mainGame->getTowerVector().size(); i++) {
            mainGame->getTowerVector()[i]->draw(window);
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

        //Checks if round is over and allows the start of next round if so
        if (mainGame->getStopSpawn() && mainGame->getEnemyVector().empty()) {
            window.draw(*mainGame->getRoundText());
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                mainGame->setStopSpawn(false);
            }
        }

        window.display();
    }

    return 0;
}