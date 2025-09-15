#pragma once
#include "Player.h"

class monster;

class Archer : public Player
{
public:

	Archer(string nickname);

	void attack();
	void attack(Monster* monster);
};