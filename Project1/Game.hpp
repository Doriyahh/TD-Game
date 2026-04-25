#pragma once


// Primary class for player values. May also end up containing game wrapper.
class Game {
public:
	int getGold(void) { return this->mPlayerGold; }
	int getHealth(void) { return this->mPlayerHealth; }
	void setGold(int input) { this->mPlayerGold = input; }
	void setHealth(int input) { this->mPlayerHealth = input; }
private:
	int mPlayerGold = 650; // Central player gold count, will update upon tower purchase or enemy defeat
	int mPlayerHealth = 150; // Player health count. Reduces if enemy reaches end, game ends if reaches zero
};