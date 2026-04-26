#include "Game.hpp"
#include "Enemy.hpp"
#include <algorithm>

void Game::removeEnemy(Enemy* target) {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [target](const Enemy& e) {
                return &e == target; // Compare addresses
            }),
        enemies.end()
    );
}

void Game::removeTower(Tower* target) {
    towers.erase(
        std::remove_if(towers.begin(), towers.end(),
            [target](const Tower& t) {
                return &t == target; // Compare addresses
            }),
        towers.end()
    );
}

void Game::removeProjectile(Projectile* target) {
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [target](const Projectile& p) {
                return &p == target; // Compare addresses
            }),
        projectiles.end()
    );
}