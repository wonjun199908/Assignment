#include <iostream>
#include <string>
#include "Archer.h"
#include "Monster.h"

using namespace std;


Archer::Archer(string nickname)
{

}

void Archer::attack()
{
	cout << "궁수 공격" << endl;
}

void Archer::attack(Monster* monster)
{
	int damage = 0;
	int totaldamage = 0;
	
	for (int i = 0; i < 3; i++)
	{
		damage = (getPower() - monster->getDefence()) / 3;

		if (damage <= 0)
		{
			damage = 1;
		}

		totaldamage += damage;

		cout << monster->getname() << "에게 화살로 피해를 " << damage << "입혔다." << endl;
	}


	if (monster->setHP(monster->getHP() - totaldamage))
	{
		cout << "몬스터의 남은 체력:  " << monster->getHP() << endl;
	}
	else
	{
		cout << "몬스터의 남은 체력:  " << monster->getHP() << endl << "플레이어 승리" << endl;
	}
}