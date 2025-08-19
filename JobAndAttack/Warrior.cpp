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
	cout << "���� ����" << endl;
}

void Warrior::attack(Monster* monster)
{
	int damage = getPower() - monster->getDefence();

	if (damage <= 0)
	{
		damage = 1;
	}
	cout << monster->getname() << "���� ������ ���ظ� " << damage << "������." << endl;

	if (monster->setHP(monster->getHP() - damage))
	{
		cout << "������ ���� ü��:  " << monster->getHP() << endl;
	}
	else
	{
		cout << "������ ���� ü��:  " << monster->getHP() << endl << "�÷��̾� �¸�" << endl;
	}

}
