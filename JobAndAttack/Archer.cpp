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
	cout << "�ü� ����" << endl;
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

		cout << monster->getname() << "���� ȭ��� ���ظ� " << damage << "������." << endl;
	}


	if (monster->setHP(monster->getHP() - totaldamage))
	{
		cout << "������ ���� ü��:  " << monster->getHP() << endl;
	}
	else
	{
		cout << "������ ���� ü��:  " << monster->getHP() << endl << "�÷��̾� �¸�" << endl;
	}
}