#pragma once

#include <iostream>
#include <vector>
#include <string>

class PotionRecipe;
class AlchemyWorkshop
{
public:
	AlchemyWorkshop(); 

private:
	std::vector<PotionRecipe*> recipes;

public:


public:
	void addRecipe(const std::string& name, const std::vector<std::string>& ingredients);

	void displayAllRecipes() const;

	PotionRecipe* searchRecipeByName(const std::string& name);

	std::vector<PotionRecipe*> searchRecipeByIngredient(const std::string ingredient); 
};

