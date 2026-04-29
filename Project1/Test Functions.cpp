#include "Test Functions.hpp"
#include "Projectile.hpp"
#include "Tower.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include <cassert>
#include <cmath>

// tests whether Projectile::checkHit correctly detects collision between projectile and enemy
bool testProjectileCheckHit()
{
    // create a minimal Game object to satisfy constructors that need a Game*
    Game g;
    Game* game = &g;

    // create a projectile centered at (100,100) with radius 5.
    // the constructor sets position and radius and stores the Game* pointer.
    Projectile proj(game, sf::Vector2f(100.f, 100.f), 5.f, 0.f, 1.f, 1.f, 1.f);

    // create a simple enemy and place it exactly at the projectile position.
    // using matching coordinates ensures circles are overlapping and should
    // therefore be detected by checkHit.
    Enemy* e = new Enemy(game, 10.f, 10.f, 1.f, 1.f, 1.f, 1.f);
    e->setPosition(sf::Vector2f(100.f, 100.f));

    // call the collision check and capture result.
    bool hit = proj.checkHit(e);
    delete e;
    // return true when collision detection reports a hit.
    return hit == true;
}

// tests Projectile::searchEnemy and getHitEnemies vector handling
bool testProjectileSearchEnemy()
{
    // create minimal game and projectile instances
    Game g;
    Game* game = &g;
    Projectile proj(game, sf::Vector2f(0.f, 0.f), 5.f, 0.f, 1.f, 1.f, 1.f);

    // create an enemy pointer to use for membership checks
    Enemy* e = new Enemy(game, 10.f, 10.f, 1.f, 1.f, 1.f, 1.f);

    // initially, the projectile's hit-list should not contain this enemy.
    bool before = proj.searchEnemy(e);

    // add the enemy to the internal hit list and verify searchEnemy returns true.
    proj.getHitEnemies().push_back(e);
    bool after = proj.searchEnemy(e);

    bool result = (!before) && after;

    // clear the hit list and free the enemy memory.
    proj.getHitEnemies().clear();
    delete e;
    return result;
}

// tests tower range setter and getter consistency
bool testTowerRangeSetGet()
{
    // create game and tower, set a new range and verify getter matches.
    Game g;
    Game* game = &g;
    Tower t(game, sf::Vector2f(200.f,200.f), 1.f, 1.f, 50.f);

    // update the range using the public setter. This also updates the
    // associated range circle origin/radius inside Tower::setRange.
    t.setRange(120.f);

    // use a small epsilon to compare floating point values.
    return std::abs(t.getRange() - 120.f) < 0.001f;
}

// tests basic placement validity logic by placing a tower inside and outside map bounds
bool testTowerPlacementValidity()
{
    // create game and a tower positioned roughly in the playable area.
    Game g;
    Game* game = &g;
    Tower* t = new Tower(game, sf::Vector2f(200.f,200.f), 1.f, 1.f, 50.f);

    // check placement validity for a reasonable in-map position. The
    // implementation of isPlacementValid checks tower collisions with other
    // towers, collisions with map paths and finally checks intersection
    // against a hard-coded playable rect; here we only test the last
    // condition by using different positions.
    bool inside = t->isPlacementValid();

    // move tower near the top-left to intentionally place it outside the
    // good placement rectangle and verify validity becomes false.
    t->setPosition(sf::Vector2f(10.f, 10.f));
    bool outside = t->isPlacementValid();

    delete t;
    return inside && !outside;
}

// tests Enemy::move progression through waypoints and reachedEnd
bool testEnemyMoveAndReachedEnd()
{
    // create game and a short waypoint list so movement can be exercised.
    Game g;
    Game* game = &g;
    std::vector<sf::Vector2f> wp;
    wp.push_back(sf::Vector2f(0.f, 0.f));
    wp.push_back(sf::Vector2f(10.f, 0.f));

    // create an Enemy with sufficient speed so calling update once should
    // advance it toward or to the next waypoint.
    Enemy* e = new Enemy(game, 1.f, 1.f, 1.f, 5.f, 5.f, 1.f);

    // assign the waypoint list and set a starting position matching the
    // first waypoint so the next call to update will progress the index.
    e->getWaypoints() = wp;
    e->setPosition(sf::Vector2f(0.f, 0.f));

    // call update which internally calls move(). The movement implementation
    // advances the current waypoint index when the enemy gets close enough.
    e->update(); // should move towards next waypoint or mark reached

    // consider the test successful if the enemy advanced to the next
    // waypoint index or reported it reached the end.
    bool movedOrReached = e->getCurrentWaypoint() > 0 || e->reachedEnd();

    delete e;
    return movedOrReached;
}


