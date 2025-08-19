#include <iostream>
#include "Player.h"
#include "Warrior.h"
#include "Magician.h"
#include "Thief.h"
#include "Archer.h"
#include "Monster.h"
using namespace std;

// ���� �Լ�
int main() {
    string jobs[] = { "����", "������", "����", "�ü�" };
    int job_choice = 0;
    string nickname;

    Player* player[4];

    cout << "* �г����� �Է����ּ���: ";
    cin >> nickname;

    cout << "<���� �ý���>" << endl;
    cout << nickname << "��, ȯ���մϴ�!" << endl;
    cout << "* ���Ͻô� ������ �������ּ���." << endl;

    for (int i = 0; i < 4; i++) {
        cout << (i + 1) << ". " << jobs[i] << endl;
    }

    cout << "����: ";
    cin >> job_choice;


    switch (job_choice) {
    case 1:
        player[0] = new Warrior(nickname);
        break;
    case 2:
        player[1] = new Magician(nickname);
        break;
    case 3:
        player[2] = new Thief(nickname);
        break;
    case 4:
        player[3] = new Archer(nickname);
        break;
    default:
        cout << "�߸��� �Է��Դϴ�." << endl;
        return 1;
    }
    

    int job_index = job_choice - 1;

    player[job_index]->setJob_name(jobs[job_index]);
    player[job_index]->attack();
    player[job_index]->printPlayerStatus();

    Monster* monster;

    monster = new Monster("������");



    while (player[job_index]->getHP() > 0 && monster->getHP() > 0)
    {
        player[job_index]->attack(monster);

       if (monster->getHP() > 0)
       {
           monster->attack(player[job_index]);
       }

        
    }
    
    delete player[job_index];
    delete monster;

    return 0;
}

