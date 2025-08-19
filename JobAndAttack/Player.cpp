#include <iostream>
#include "Player.h"


Player::Player(string nickname)
{
    setNickname(nickname);

 
}

void Player::printPlayerStatus()
{  
    cout << "------------------------------------" << endl;
    cout << "* ���� �ɷ�ġ" << endl;
    cout << "�г���: " << nickname << endl;
    cout << "����: " << job_name << endl;
    cout << "Lv. " << level << endl;
    cout << "HP: " << HP << endl;
    cout << "MP: " << MP << endl;
    cout << "���ݷ�: " << power << endl;
    cout << "����: " << defence << endl;
    cout << "��Ȯ��: " << accuracy << endl;
    cout << "�ӵ�: " << speed << endl;
    cout << "------------------------------------" << endl;
}

void Player::setNickname(string nickname)
{
    this->nickname = nickname;
}

void Player::setJob_name(string job_name)
{
    this->job_name = job_name;
}

bool Player::setHP(int HP)
{
    this->HP = HP;

    if (this->getHP() <= 0)
    {
        this->HP = 0;

        return false;
    }

    

    return true;
}

bool Player::setMP(int MP)
{
    this->MP = MP;

    return false;
}

void Player::setPower(int power)
{
    this->power = power;
}

void Player::setDefence(int defence)
{
    this->defence = defence;
}

void Player::setAccuracy(int accuracy)
{
    this->accuracy = accuracy;
}

void Player::setSpeed(int speed)
{
    this->speed = speed;
}
