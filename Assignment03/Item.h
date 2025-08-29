#pragma once
#include <string>
using namespace std;

class Item
{
public:

	Item()
	{
		SetItemName("Item");
		SetItemPrice(0);
	}

	string GetItemName() const{ return name_; }
	int GetItemPrice() const { return price_; }

	void SetItemName(string itemname) { this->name_ = itemname;}
	void SetItemPrice(int Itemprice) { this->price_ = Itemprice; }
protected:
	string name_;
	int price_;

};