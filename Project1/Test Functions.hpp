#pragma once
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
#include "EndMenu.hpp"

// AI DISCREPANCY: 2/5 of the following test function declarations and implementations were partially created with AI assistance. 
// 5/5 Test Functions in Test Functions.cpp comments and descriptions were written and summarized by AI. 
 

// 1) testProjectileCheckHit
//    - verify Projectile::checkHit detects when a projectile and an
//      enemy occupy overlapping positions.
//    - construct a Projectile and an Enemy at the same coordinates and
//      return whether checkHit reports a collision.
bool testProjectileCheckHit();

// 2) testProjectileSearchEnemy
//    - verify Projectile::searchEnemy correctly reports whether an
//      Enemy pointer is present in the projectile's internal hit list.
//    - create a Projectile, create an Enemy pointer, ensure searchEnemy
//      returns false initially, push the pointer into the projectile's
//      hit-list, then verify searchEnemy returns true.
bool testProjectileSearchEnemy();

// 3) testTowerRangeSetGet
//    - ensure Tower::setRange updates internal state and that
//      getRange returns the expected value.
//    - create a Tower, call setRange with a new value, verify
//      getRange returns that value.
bool testTowerRangeSetGet(); // DISCREPANCY: AI PARTIALLY USED FOR CREATION OF testTowerRangeSetGet()
							

// 4) testTowerPlacementValidity
//    - exercise Tower::isPlacementValid to check behavior for a
//      tower placed inside the playable map region vs near the border.
//    - create a Tower positioned in the map area and one near the
//      outside; verify the function returns true for inside and false for
//      outside as expected.
bool testTowerPlacementValidity();

// 5) testEnemyMoveAndReachedEnd
//    - verify Enemy movement progresses through a simple waypoint
//      list and that reachedEnd() becomes true when waypoints are exhausted.
//    - assign a short waypoint list to an Enemy, call update() once or
//      twice and check whether the current waypoint index advanced or the
//      enemy reports it reached the end.
bool testEnemyMoveAndReachedEnd(); // DISCREPANCY: AI PARTIALLY USED FOR CREATION OF testEnemyMoveAndReachedEnd()
								   
