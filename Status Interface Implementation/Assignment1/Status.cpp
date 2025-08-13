#include <iostream>
using namespace std;


void setHpMp(int* Hp, int* Mp)
{
	cin >> *Hp >> *Mp;
}

void setAtkDef(int* Atk, int* Def)
{
	cin >> *Atk >> *Def;
}

void setPotion(int count, int* p_HPPotion, int* p_MPPotion)
{
	*p_HPPotion = count;
	*p_MPPotion = count;

	cout << "* 포션이 지급되었습니다. (HP, MP 포션 각" << count << "개)" << endl;
}

void status_management_system()
{
	cout << "=============================================" << endl;
	cout << "<스탯 관리 시스템>" << endl;
	cout << "1. HP 회복" << endl;
	cout << "2. MP 회복" << endl;
	cout << "3. HP 강화" << endl;
	cout << "4. MP 강화" << endl;
	cout << "5. 공격 스킬 사용" << endl;
	cout << "6. 필살기 사용" << endl;
}


int main()
{
	int status[4] = { 0,0,0,0 };

	cout << "HP와 MP를 입력해주세요: "; 
	setHpMp(&status[0], &status[1]);

	while (status[0] <= 50 || status[1] <= 50)
	{
		cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요.";
		setHpMp(&status[0], &status[1]);
	}

	cout << "공격력과 방어력을 입력해주세요: ";
	setAtkDef(&status[2], &status[3]);
	
	while (status[2] <= 0 || status[3] <= 0)
	{
		cout << "공격력이나 방어력 값이 너무 작습니다. 다시 입력해주세요.";
		setAtkDef(&status[2], &status[3]);
	}

	int postion_Hp = 0;
	int postion_Mp = 0;

	setPotion(5, &postion_Hp, &postion_Mp);

	status_management_system();

	int num = 0;
	int posion_increase = 20;

	int skill_Mp = 50;

	while (true)
	{
		cout << "번호를 선택해주세요: ";
		cin >> num;

		switch (num)
		{
		case 1:

			if (postion_Hp <= 0)
			{
				cout << "포션이 부족합니다." << endl;
				break;
			}
			cout << "* HP가 " << posion_increase << "회복되었습니다.포션이 1개 차감됩니다." << endl;

			status[0] += posion_increase;
			cout << "현재 HP: " << status[0] << endl;

			postion_Hp--;
			cout << "남은 포션 수: " << postion_Hp << endl;
			break;
		case 2:
			if (postion_Mp <= 0)
			{
				cout << "포션이 부족합니다." << endl;
				break;
			}

			cout << "* MP가 " << posion_increase << "회복되었습니다.포션이 1개 차감됩니다." << endl;

			status[1] += posion_increase;
			cout << "현재 MP: " << status[1] << endl;

			postion_Mp--;
			cout << "남은 포션 수: " << postion_Mp << endl;
			break;
		case 3:
			cout << "HP가 2배로 증가되었습니다." << endl;
			status[0] *= 2;

			cout << "현재 HP: " << status[0] << endl;
			break;
		case 4:
			cout << "MP가 2배로 증가되었습니다." << endl;
			status[1] *= 2;

			cout << "현재 MP: " << status[1] << endl;
			break;

		case 5:
			if (status[1] < 50)
			{
				cout << "스킬 사용이 불가합니다." << endl;
				break;
			}

			cout << "스킬을 사용하여 MP가 " << skill_Mp << " 소모되었습니다." << endl;
			status[1] -= skill_Mp;

			cout << "현재 MP: " << status[1] << endl;
			break;

		case 6:
			if (status[1] < 100)
			{
				cout << "MP가 부족해 필살기를 사용 할 수 없습니다." << endl;
				break;
			}
			
			cout << "필살기를 사용하여 MP가 50% 소모되었습니다." << endl;
			status[1] /= 2;

			cout << "현재 MP: " << status[1] << endl;
			break;

		case 7:
			cout << "프로그램을 종료합니다." << endl;

			return 0;

		default:
			break;
		}
	}

	return 0;
}