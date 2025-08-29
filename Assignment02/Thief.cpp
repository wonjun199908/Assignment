#include <iostream>
#include <string>
#include "Thief.h"
#include "Monster.h"
using namespace std;


Thief::Thief(string nickname)
{

}

void Thief::attack()
{
	cout << "도적 공격" << endl;
}

void Thief::attack(Monster* monster)
{
	int damage;

	for (int i = 0; i < 5; i++)
	{
		damage = (getPower() - monster->getDefence()) / 5;

		if (damage <= 0)
		{
			damage = 1;
		}

		cout << monster->getname() << "에게 단검으로 피해를 " << damage << "입혔다." << endl;

		if (monster->setHP(monster->getHP() - damage))
		{
			cout << "몬스터의 남은 체력:  " << monster->getHP() << endl;
		}
		else
		{
			cout << "몬스터의 남은 체력:  " << monster->getHP() << endl << "플레이어 승리" << endl;
		}

	}


	
}