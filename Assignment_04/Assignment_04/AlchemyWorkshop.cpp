#include "AlchemyWorkshop.h"
#include "PotionRecipe.h"
#include "Potion.h"

AlchemyWorkshop::AlchemyWorkshop()
{
}

void AlchemyWorkshop::addRecipe(const std::string& name, const std::vector<std::string>& ingredients)
{
	PotionRecipe* NewRecipe = new PotionRecipe(name, ingredients);

	recipes.push_back(NewRecipe);

	std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다.\n";
	std::cout << "(총 레시피 수 : " << recipes.size() << "개) \n"; 
}

void AlchemyWorkshop::displayAllRecipes() const
{
	if (recipes.empty())
	{
		std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
		return;
	}

	std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;

	for (auto& recipe : recipes)
	{
		std::cout << "- 물약 이름: " << recipe->getName() << std::endl;
		std::cout << "  > 필요 재료: ";

		for (size_t j = 0; j < recipe->getIngredients().size(); ++j)
		{
			std::cout << recipe->getIngredients()[j];
			// 마지막 재료가 아니면 쉼표로 구분
			if (j < recipe->getIngredients().size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
		std::cout << "---------------------------\n";
	}


}

PotionRecipe* AlchemyWorkshop::searchRecipeByName(const std::string& name)
{
	for (auto& recipe : recipes)
	{
		if (recipe->getName() == name) return recipe;
	}

	return nullptr;
}

std::vector<PotionRecipe*> AlchemyWorkshop::searchRecipeByIngredient(const std::string ingredient)
{
	std::vector<PotionRecipe*> result;

	for (const auto& recipe : recipes)
	{
		for(const std::string& ing : recipe->getIngredients())	
		{
			// 레시피에 재료가 포함되면 그 레시피를 배열에 넣음. 
			if (ing == ingredient)
			{
				result.push_back(recipe);
			}
		}
	}
	 
	return result;
}


