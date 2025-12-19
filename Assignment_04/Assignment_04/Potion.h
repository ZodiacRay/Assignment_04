#pragma once
#include <string>

class PotionRecipe;

class Potion
{
public:
	Potion() { name = ""; }

	Potion(std::string name) : name(name) {}

	std::string getName() { return name; }

private:
	std::string name; 



};

