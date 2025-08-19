#include <iostream>
#include "Player.h"
#include "Warrior.h"
#include "Magician.h"
#include "Thief.h"
#include "Archer.h"
#include "Monster.h"
using namespace std;

// 메인 함수
int main() {
    string jobs[] = { "전사", "마법사", "도적", "궁수" };
    int job_choice = 0;
    string nickname;

    Player* player[4];

    cout << "* 닉네임을 입력해주세요: ";
    cin >> nickname;

    cout << "<전직 시스템>" << endl;
    cout << nickname << "님, 환영합니다!" << endl;
    cout << "* 원하시는 직업을 선택해주세요." << endl;

    for (int i = 0; i < 4; i++) {
        cout << (i + 1) << ". " << jobs[i] << endl;
    }

    cout << "선택: ";
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
        cout << "잘못된 입력입니다." << endl;
        return 1;
    }
    

    int job_index = job_choice - 1;

    player[job_index]->setJob_name(jobs[job_index]);
    player[job_index]->attack();
    player[job_index]->printPlayerStatus();

    Monster* monster;

    monster = new Monster("슬라임");



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

