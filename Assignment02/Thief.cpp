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
	cout << "���� ����" << endl;
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

		cout << monster->getname() << "���� �ܰ����� ���ظ� " << damage << "������." << endl;

		if (monster->setHP(monster->getHP() - damage))
		{
			cout << "������ ���� ü��:  " << monster->getHP() << endl;
		}
		else
		{
			cout << "������ ���� ü��:  " << monster->getHP() << endl << "�÷��̾� �¸�" << endl;
		}

	}


	
}