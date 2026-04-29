#include "Game.hpp"
#include "Enemy.hpp"
#include <algorithm>
#include "Tower.hpp"
#include "BaseEnemy.hpp"
#include "FasterEnemy.hpp"
#include "HealerEnemy.hpp"
#include "Boss.hpp"
#include "Tank.hpp"

void Game::roundHandler()
{
    //Get the line from the file
    if (std::getline(*this->mRoundStream, this->mRoundString)) {

        //Create a string stream to handle tokenizing
        this->mRoundStringStream.str(this->mRoundString);
        std::string token;
        this->mRoundStringStream.clear();
        this->mRoundStringStream.seekg(0, std::ios::beg);

        //Get spawn timer
        std::getline(this->mRoundStringStream, token, ',');
        this->mSpawnTimer = std::stoi(token);

        //Get associated round
        std::getline(this->mRoundStringStream, token, ',');
        //If the round is not the same as the last enemy, postpone spawning
        if (this->mRound != std::stoi(token)) {
            this->stopSpawn = true;
        }
        this->mRound = std::stoi(token);

        //Get enemy type
        std::getline(this->mRoundStringStream, token, '\n');

        Game* pGame = this;
        
        //Create enemy based on found type
        //Spawning will be handled elsewhere
        if (token == "BasicEnemy") {
            this->newEnemy = new BasicEnemy1(pGame, this->getMap().getWaypoints());
        } else if (token == "FastEnemy") {
            this->newEnemy = new FastEnemy(pGame, this->getMap().getWaypoints());
        }
        else if (token == "HealerEnemy") {
            this->newEnemy = new HealerEnemy(pGame, this->getMap().getWaypoints());
        }
        else if (token == "BossEnemy") {
            this->newEnemy = new BossEnemy(pGame, this->getMap().getWaypoints());
        }
        else if (token == "TankEnemy") {
            this->newEnemy = new TankEnemy(pGame, this->getMap().getWaypoints());
        }
    }
    else
    {
        this->stopSpawn = true;
        this->newEnemy = nullptr;
    }
}

void Game::removeEnemy(Enemy* target) {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [target](Enemy* e) { // Change type here
                return e == target;
            }),
        enemies.end()
    );
}

void Game::removeTower(Tower* target) {
    towers.erase(
        std::remove_if(towers.begin(), towers.end(),
            [target](Tower* e) { // Change type here
                return e == target;
            }),
        towers.end()
    );
}

void Game::removeProjectile(Projectile* target) {
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [target](Projectile* e) { // Change type here
                return e == target;
            }),
        projectiles.end()
    );
}

void Game::removeLaser(sf::RectangleShape* target) {
    lasers.erase(
        std::remove_if(lasers.begin(), lasers.end(),
            [target](sf::RectangleShape* e) { // Change type here
                return e == target;
            }),
        lasers.end()
    );
}