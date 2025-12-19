#pragma once
#include <map>
#include <vector>
#include <string>

#define MAX_STOCK 3 

class StockManager
{
public:
	StockManager();

	void InitializeStock(std::string potionName);

	bool dispensePotion(std::string potionName);

	void returnPotion(std::string potionName);

	std::vector<std::string> DispensePotionsByIngredient(const std::string& ingredient);


	int getStock(std::string potionName) { return potionStock[potionName]; }

private:
	std::map<class PotionRecipe, int> potionStock;
	

};

