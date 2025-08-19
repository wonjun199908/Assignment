#include <iostream>
#include "Monster.h"
#include "Player.h"


Monster::Monster(string name)
{
	setName(name);

	setHP(10);
	setPower(30);
	setDefence(10);
	setSpeed(10);
}


void Monster::attack(Player* player)
{
	int damage = getPower() - player->getDefence();

	if (damage <= 0)
	{
		damage = 1;
	}

	cout << "플레이어에게 " << damage << " 피해를 입혔습니다." << endl;

	if (player->setHP(player->getHP() - damage))
	{
		cout << "플레이어의 남은 체력: " << player->getHP() << endl;;
	}
	else
	{
		cout << "플레이어의 남은 체력: 0" << endl << "몬스터 승리" << endl;
	}

}

void Monster::setName(string name)
{
	this->name = name;
}

bool Monster::setHP(int HP)
{
	this->HP = HP;

	if (getHP() <= 0)
	{
		this->HP = 0;

		return false;
	}
	
	return true;
}

void Monster::setPower(int power)
{
	this->power = power;
}

void Monster::setDefence(int defence)
{
	this->defence = defence;
}

void Monster::setSpeed(int speed)
{
	this->speed = speed;
}