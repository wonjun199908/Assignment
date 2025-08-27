#pragma once
#include "Item.h"

class Weapon : public Item
{
public:

	Weapon()
	{
		SetItemName("sword");
		SetItemPrice(500);
	}

};