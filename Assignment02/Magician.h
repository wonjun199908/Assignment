#pragma once
#include "Player.h"

class Monster;

class Magician : public Player
{
public:
	Magician(string nickname);

	void attack();
	void attack(Monster* monster);
};