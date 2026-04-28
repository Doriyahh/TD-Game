#include "Game.hpp"
#include "Enemy.hpp"
#include <algorithm>

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