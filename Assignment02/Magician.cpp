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
	cout << "������ ����" << endl;
}

void Magician::attack(Monster* monster)
{

	cout << "test1" << endl;

	int damage = getPower() - monster->getDefence();

	if (damage <= 0)
	{
		damage = 1;
	}
	cout << monster->getname() << "���� �������� ���ظ� " << damage << "������." << endl;

	if (monster->setHP(monster->getHP() - damage))
	{
		cout << "������ ���� ü��:  " << monster->getHP() << endl;
	}
	else
	{
		cout << "������ ���� ü��:  " << monster->getHP() << endl << "�÷��̾� �¸�" << endl;
	}
}