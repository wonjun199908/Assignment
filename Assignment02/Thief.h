#pragma once
#include "Player.h"

class Monster;

class Thief: public Player
{

public:

	Thief(string nickname);

	void attack();
	void attack(Monster* monster);
};