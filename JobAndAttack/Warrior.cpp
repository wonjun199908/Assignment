#include <iostream>
#include <string>
#include "Warrior.h"
#include "Monster.h"

using namespace std;

Warrior::Warrior(string nickname)
{
	setNickname(nickname);
}

void Warrior::attack()
{
	cout << "전사 공격" << endl;
}

void Warrior::attack(Monster* monster)
{
	int damage = getPower() - monster->getDefence();

	if (damage <= 0)
	{
		damage = 1;
	}
	cout << monster->getname() << "에게 검으로 피해를 " << damage << "입혔다." << endl;

	if (monster->setHP(monster->getHP() - damage))
	{
		cout << "몬스터의 남은 체력:  " << monster->getHP() << endl;
	}
	else
	{
		cout << "몬스터의 남은 체력:  " << monster->getHP() << endl << "플레이어 승리" << endl;
	}

}
