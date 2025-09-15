#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Inventory
{

public:
	Inventory(int capacity = 10)
	{
		capacity_ = (capacity > 0) ? capacity : 1;

		cout << capacity_ << endl;
	}

private:
	T* pitems_;
	int capacity_;
	int size_;
};


//int main()
//{
	//Inventory<int>(20);

	//return 0;
//}