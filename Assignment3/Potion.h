#pragma once
#include "Item.h"

class Potion : public Item
{
public:
	Potion()
	{
		SetItemName("HP Potion");
		SetItemPrice(100);
	}

};