#include "Game.hpp"
#include "Enemy.hpp"
#include <algorithm>

void Game::removeEnemy(Enemy* target) {
    // 1. Find the tower in the vector
    auto it = std::find(enemies.begin(), enemies.end(), target);

    if (it != enemies.end()) {
        // 2. Delete the memory first
        delete* it;

        // 3. Remove the pointer from the vector
        enemies.erase(it);
    }
}

void Game::removeTower(Tower* target) {
    // 1. Find the tower in the vector
    auto it = std::find(towers.begin(), towers.end(), target);

    if (it != towers.end()) {
        // 2. Delete the memory first
        delete* it;

        // 3. Remove the pointer from the vector
        towers.erase(it);
    }
}

void Game::removeProjectile(Projectile* target) {
    // 1. Find the tower in the vector
    auto it = std::find(projectiles.begin(), projectiles.end(), target);

    if (it != projectiles.end()) {
        // 2. Delete the memory first
        delete* it;

        // 3. Remove the pointer from the vector
        projectiles.erase(it);
    }
}

void Game::removeLaser(sf::RectangleShape* target) {
    // 1. Find the tower in the vector
    auto it = std::find(lasers.begin(), lasers.end(), target);

    if (it != lasers.end()) {
        // 2. Delete the memory first
        delete* it;

        // 3. Remove the pointer from the vector
        lasers.erase(it);
    }
}