#include "StockManager.h"
#include "PotionRecipe.h"


StockManager::StockManager()
{
}

void StockManager::InitializeStock(std::string potionName)
{
	potionStock[potionName] = MAX_STOCK;

}

bool StockManager::dispensePotion(std::string potionName)
{
	if (potionStock[potionName] <= 0) return false; 

	potionStock[potionName]--;

	return true; 
}

void StockManager::returnPotion(std::string potionName)
{
	// 공병 반환? 
	// 그러면 빈병 인지 아닌지 까지 체크를 해줘야하는데 
}

std::vector<std::string> StockManager::DispensePotionsByIngredient(const std::string& ingredient)
{

	// 해당 재료를 포함하는 레시피들 중, 재고 있는 것들을 지급처리
	// 반환: 실제로 지급된 물약 이름 목록(없으면 빈 벡터)
	std::vector<std::string> result;

	for (auto it = potionStock.begin(); it != potionStock.end(); it++)
	{
		for (std::string ing : it->first.getIngredients())
		{
			if (ing == ingredient)
			{
				dispensePotion(it->first.getName()); 
			}
		}
	}

	return result; 
}
