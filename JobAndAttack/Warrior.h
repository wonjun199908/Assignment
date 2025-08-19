#pragma once
#include "Player.h"

class Monster;

class Warrior : public Player
{
public:

	Warrior(string nickname);

	void attack();
	void attack(Monster* monster);
};