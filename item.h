//This file currently serves no purpose as I'm not even drawing rudimentary item information yet

#pragma once

#include <string>

//This class will need much fleshing out for actual use, but for now, just a name will do

class item{
public:
	item(std::string name){
		item::name = name;
		unlocked = false;
		purchasable = true;
	}
	std::string get_name(){ return name; }
	bool get_unlocked() { return unlocked; }
	bool get_purchasable() { return purchasable; }
private:
	std::string name;
	bool unlocked;
	bool purchasable;
};
