#pragma once
#include <iostream>
#include <algorithm>
#include "Item.h"
#include "Weapon.h"
#include "Potion.h"

using namespace std;

bool compareItemsByPrice(const Item& a, const Item& b) {
	return a.GetItemPrice() < b.GetItemPrice();
}


template <typename T>
class Inventory
{

public:
	Inventory(int capacity = 10)
	{
		capacity_ = (capacity > 0) ? capacity : 1;

		pitems_ = new T[capacity_];
	}

	Inventory(const Inventory<T>& other) {
		capacity_ = other.capacity_;
		size_ = other.size_;
		pitems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pitems_[i] = other.pitems_[i];
		}

		cout << "�κ��丮 ���� �Ϸ�" << endl;
	}

	~Inventory()
	{
		delete[] pitems_;

		pitems_ = nullptr;
	}

	void Assign(const Inventory<T>& other)
	{
		delete[] pitems_;

		capacity_ = other.capacity_;
		size_ = other.size_;
		pitems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pitems_[i] = other.pitems_[i];
		}
		cout << "�κ��丮 ���� �Ϸ�" << endl;
	}


	void AddItem(const T& item)
	{

		if (size_ < capacity_)
		{
			pitems_[size_] = item;

			size_++;

			cout << "�κ��丮�� �������� �߰� �Ǿ����ϴ�." << endl;
		}
		else
		{
			cout << "�κ��丮�� �� á���ϴ�. �κ��丮�� 2�� �ø��ϴ�." << endl;

			

			Resize(capacity_ * 2);

			pitems_[size_] = item;

			size_++;

			cout << "�κ��丮�� �������� �߰� �Ǿ����ϴ�." << endl;

		}
	}

	void Resize(int newCapacity)
	{
		if (size_ > newCapacity)
		{
			cout << "����� ���� �� �� �����ϴ�." << endl;

			return;
		}


		T* pitems2_ = new T[newCapacity];

		for (int i = 0; i < size_; i++)
		{
			pitems2_[i] = pitems_[i];
		}

		capacity_ = newCapacity;


		delete[] pitems_;

		pitems_ = pitems2_;
	}

	void SortItems()
	{
		sort(pitems_, pitems_ + size_, compareItemsByPrice);

		cout << "�������� ���ݼ����� �����߽��ϴ�." << endl;
	}


	void RemoveLastItem()
	{
		if (size_ <= 0)
		{
			cout << "�κ��丮�� ����ֽ��ϴ�." << endl;

			return;
		}
		size_--;
	}


	int GetSize() const { return size_; }
	int GetCapacity() const { return capacity_; }


	void PrintInfo() const 
	{
		for (int i = 0; i < size_; i++)
		{
			cout << "[�̸�: " << pitems_[i].GetItemName() << ", ����: " << pitems_[i].GetItemPrice() << "G]" << endl;
		}	
	}


private:
	T* pitems_;
	int capacity_;
	int size_ = 0;
};




int main()
{
	Inventory<Item> inven(4);
	Weapon* sword = new Weapon;
	Potion* HPPotion = new Potion;


	inven.AddItem(*sword);
	inven.AddItem(*HPPotion);
	
	inven.PrintInfo();
	//inven.RemoveLastItem();
	
	/*Inventory<Item> inven2 = inven;
	inven2.PrintInfo();

	Inventory<Item> inven3(10);
	inven3.Assign(inven);
	inven3.PrintInfo();
	*/

	inven.SortItems();
	inven.PrintInfo();
	return 0;
}