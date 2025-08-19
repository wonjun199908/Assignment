#pragma once
#include <string>
using namespace std;

class Player;

class Monster 
{
public: 

	Monster(string name);

	Monster() {

	};

	void attack(Player* player);

	string getname() { return name; }
	int getHP() const { return HP; }
	int getPower() { return power; }
	int getDefence() { return defence; }
	int getSpeed() { return speed; }

	void setName(string name);
	bool setHP(int HP);
	void setPower(int power);
	void setDefence(int defence);
	void setSpeed(int speed);

protected:
	string name;
	int HP;
	int power; 
	int defence; 
	int speed; 
};

