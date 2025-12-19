#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Potion.h"

class PotionRecipe
{
public:
	PotionRecipe(const std::string& name, const std::vector<std::string> ingredients) 
		: potionName(name), ingredients(ingredients) 
	{}

	const std::string getName() const { return potionName; }

	const std::vector<std::string> getIngredients() const {	return ingredients;	}

private:
	std::string potionName;
	std::vector<std::string> ingredients;

};

