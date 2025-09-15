#include <iostream>
#include <string>
#include "Magician.h"
#include "Monster.h"

using namespace std;


Magician::Magician(string nickname)
{

}

void Magician::attack()
{
	cout << "마법사 공격" << endl;
}

void Magician::attack(Monster* monster)
{

	cout << "test1" << endl;

	int damage = getPower() - monster->getDefence();

	if (damage <= 0)
	{
		damage = 1;
	}
	cout << monster->getname() << "에게 마법으로 피해를 " << damage << "입혔다." << endl;

	if (monster->setHP(monster->getHP() - damage))
	{
		cout << "몬스터의 남은 체력:  " << monster->getHP() << endl;
	}
	else
	{
		cout << "몬스터의 남은 체력:  " << monster->getHP() << endl << "플레이어 승리" << endl;
	}
}