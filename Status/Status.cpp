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

	cout << "* ������ ���޵Ǿ����ϴ�. (HP, MP ���� ��" << count << "��)" << endl;
}

void status_management_system()
{
	cout << "=============================================" << endl;
	cout << "<���� ���� �ý���>" << endl;
	cout << "1. HP ȸ��" << endl;
	cout << "2. MP ȸ��" << endl;
	cout << "3. HP ��ȭ" << endl;
	cout << "4. MP ��ȭ" << endl;
	cout << "5. ���� ��ų ���" << endl;
	cout << "6. �ʻ�� ���" << endl;
}


int main()
{
	int status[4] = { 0,0,0,0 };

	cout << "HP�� MP�� �Է����ּ���: "; 
	setHpMp(&status[0], &status[1]);

	while (status[0] <= 50 || status[1] <= 50)
	{
		cout << "HP�� MP�� ���� �ʹ� �۽��ϴ�. �ٽ� �Է����ּ���.";
		setHpMp(&status[0], &status[1]);
	}

	cout << "���ݷ°� ������ �Է����ּ���: ";
	setAtkDef(&status[2], &status[3]);
	
	while (status[2] <= 0 || status[3] <= 0)
	{
		cout << "���ݷ��̳� ���� ���� �ʹ� �۽��ϴ�. �ٽ� �Է����ּ���.";
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
		cout << "��ȣ�� �������ּ���: ";
		cin >> num;

		switch (num)
		{
		case 1:

			if (postion_Hp <= 0)
			{
				cout << "������ �����մϴ�." << endl;
				break;
			}
			cout << "* HP�� " << posion_increase << "ȸ���Ǿ����ϴ�.������ 1�� �����˴ϴ�." << endl;

			status[0] += posion_increase;
			cout << "���� HP: " << status[0] << endl;

			postion_Hp--;
			cout << "���� ���� ��: " << postion_Hp << endl;
			break;
		case 2:
			if (postion_Mp <= 0)
			{
				cout << "������ �����մϴ�." << endl;
				break;
			}

			cout << "* MP�� " << posion_increase << "ȸ���Ǿ����ϴ�.������ 1�� �����˴ϴ�." << endl;

			status[1] += posion_increase;
			cout << "���� MP: " << status[1] << endl;

			postion_Mp--;
			cout << "���� ���� ��: " << postion_Mp << endl;
			break;
		case 3:
			cout << "HP�� 2��� �����Ǿ����ϴ�." << endl;
			status[0] *= 2;

			cout << "���� HP: " << status[0] << endl;
			break;
		case 4:
			cout << "MP�� 2��� �����Ǿ����ϴ�." << endl;
			status[1] *= 2;

			cout << "���� MP: " << status[1] << endl;
			break;

		case 5:
			if (status[1] < 50)
			{
				cout << "��ų ����� �Ұ��մϴ�." << endl;
				break;
			}

			cout << "��ų�� ����Ͽ� MP�� " << skill_Mp << " �Ҹ�Ǿ����ϴ�." << endl;
			status[1] -= skill_Mp;

			cout << "���� MP: " << status[1] << endl;
			break;

		case 6:
			if (status[1] < 100)
			{
				cout << "MP�� ������ �ʻ�⸦ ��� �� �� �����ϴ�." << endl;
				break;
			}
			
			cout << "�ʻ�⸦ ����Ͽ� MP�� 50% �Ҹ�Ǿ����ϴ�." << endl;
			status[1] /= 2;

			cout << "���� MP: " << status[1] << endl;
			break;

		case 7:
			cout << "���α׷��� �����մϴ�." << endl;

			return 0;

		default:
			break;
		}
	}

	return 0;
}