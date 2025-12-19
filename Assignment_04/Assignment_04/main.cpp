#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Potion
{
public:

	Potion() { name = ""; }
	Potion(string inName) : name(inName) {}

	const string GetName() const{ return name; }
private:
	string name;
};

class PotionRecipe
{
public:
	// 포션 레시피 생성자 
	PotionRecipe(string InName, vector<string> InIngredient)
		:potionName(InName), ingredients(InIngredient)
	{
	}

	// 레시피에 해당 재료가 포함하는지 
	bool HasIngredientInRecipe(string ingredient)
	{
		for (string ing : ingredients)
		{
			if (ing == ingredient)
			{
				return true;
			}
		}

		return false; 
	}

	// 레시피 재료 출력 
	void PrintIngredient()
	{
		for (int i = 0; i < ingredients.size(); i++)
		{
			cout << ingredients[i];

			if (i < ingredients.size() - 1)
			{
				cout << ", ";
			}
		}

		cout << '\n';
	}

	// Getter 
	const string& GetPotionName() const { return potionName; }
	const vector<string>& GetIngredient() const  { return ingredients; }

private:
	string potionName; // 만들어지는 포션 
	vector<string> ingredients; // 재료 
};

class StockManager
{
public:
	StockManager() {}

	// 포션 재고 최댓값으로 초기화 
	void InitializeStock(string potionName)
	{
		potionStock[potionName] = MAX_STOCK;
	}

	// 포션 지급 
	bool DispensePotion(string potionName)
	{
		auto it = potionStock.find(potionName);

		// 포션이 없거나 재고가 없으면 지급 불가 
		if (it == potionStock.end() || it->second <= 0) return false; 

		// 포션 지급 
		it->second--;

		return true; 
	}

	// 공병 반환 
	void ReturnStock(string& potionName)
	{
		potionStock[potionName] = min(3, potionStock[potionName]+1);
	}

	// 재고 조회 
	int GetStockByName(const string potionName) const
	{
		auto it = potionStock.find(potionName);
		// 포션이 없음 
		if (it == potionStock.end())
		{
			return 0; 
		}

		// 재고 리턴 
		return it->second; 
	}

	static constexpr int MAX_STOCK = 3;

private:
	unordered_map<string, int> potionStock; 
};

class AlchemyWorkshop {
public:
	// 레시피 추가 
	void AddRecipe(string name, vector<string> ingredients)
	{
		recipes.push_back(PotionRecipe(name, ingredients));
		Stock.InitializeStock(name);
	}

	// 모든 레시피 출력 
	void DisplayAllRecipes() 
	{
		if (recipes.empty())
		{
			return;
		}

		cout << "\n --- [ 전체 레시피 목록 ] --- \n";

		for (const PotionRecipe& recipe : recipes)
		{
			std::cout << "- 물약 이름: " << recipe.GetPotionName() << std::endl;
			std::cout << "  > 필요 재료: ";

			for (int i = 0; i < recipe.GetIngredient().size(); i++)
			{
				cout << recipe.GetIngredient()[i];

				if (i < recipe.GetIngredient().size()-1)
				{
					cout << ", ";
				}
			}

			cout << '\n';
		}

		std::cout << "---------------------------\n";
	}

	// 이름으로 레시피 찾기 
	PotionRecipe SearchRecipeByPotionName(const string name) 
	{
		for (const PotionRecipe& recipe : recipes)
		{
			if (name == recipe.GetPotionName()) return recipe;
		}

		return PotionRecipe("NONE", {"NONE"});
	}

	// 재료가 들어가는 레시피들 찾기 
	vector<PotionRecipe> SearchRecipeByIngredient(string ingredient)
	{
		vector<PotionRecipe> result;

		for (PotionRecipe& recipe : recipes)
		{
			if (recipe.HasIngredientInRecipe(ingredient))
			{
				result.push_back(recipe);
			}
		}
		return result;
	}

	// 재료가 들어가는 레시피들 지급 
	vector<string> DispensePotionsByIngredient(const string ingredient)
	{
		vector<string> result; 

		// 재료가 들어가는 레시피들 
		vector<PotionRecipe> recipeHasIngredient = SearchRecipeByIngredient(ingredient);

		// 레시피를 못찾았으면 리턴 
		if (recipeHasIngredient.empty()) return result; 

		for (PotionRecipe& recipe : recipeHasIngredient)
		{
			string potionName = recipe.GetPotionName(); 

			// 지급 성공하면 포션이름 추가 
			if (Stock.DispensePotion(potionName))
			{
				result.push_back(potionName);
			}
		}

		return result;
	}

	// 포션 재고 출력 
	int GetStockByName(const string potionName)
	{
		return Stock.GetStockByName(potionName);
	}

	// 포션 지급 
	bool DispensePotionByName(string potionName)
	{
		return Stock.DispensePotion(potionName);
	}

	// 포션 재고 증가 
	void ReturnPotionByName(string potionName)
	{
		Stock.ReturnStock(potionName);
	}

private:

	vector<PotionRecipe> recipes; // 레시피 배열
	
	StockManager Stock; // 재고 매니저
};

int main()
{
	AlchemyWorkshop workshop;

	workshop.AddRecipe("Healing Potion", { "Herb", "Water" });
	workshop.AddRecipe("Mana Potion", { "Magic Water", "Crystal" });
	workshop.AddRecipe("Stamina Potion", { "Herb", "Berry" });
	workshop.AddRecipe("Fire Resistance Potion", { "Fire Flower", "Ash" });

	cout << "=== 초기 상태 (레시피 추가 + 재고 자동 3개) ===\n";
	workshop.DisplayAllRecipes();

	cout << "\n[재고 확인] Healing Potion 재고: "
		<< workshop.GetStockByName("Healing Potion") << "\n";

	cout << "\n=== 이름으로 지급 테스트 (Healing Potion 3회 지급) ===\n";
	cout << "1회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";
	cout << "2회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";
	cout << "3회 지급: " << (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";

	cout << "현재 재고: " << workshop.GetStockByName("Healing Potion") << "\n";

	cout << "4회 지급(재고 없으면 실패): "
		<< (workshop.DispensePotionByName("Healing Potion") ? "성공" : "실패") << "\n";

	cout << "\n=== 재료로 지급 테스트 (ingredient = Herb) ===\n";
	vector<string> dispensed = workshop.DispensePotionsByIngredient("Herb");

	cout << "지급된 물약 수: " << dispensed.size() << "\n";
	for (const std::string& name : dispensed)
		cout << "- " << name << "\n";

	cout << "\n=== 공병 반환 테스트 (Healing Potion) ===\n";
	workshop.ReturnPotionByName("Healing Potion");
	workshop.ReturnPotionByName("Healing Potion");
	workshop.ReturnPotionByName("Healing Potion"); // 이미 3이면 더 올라가면 안 됨

	cout << "반환 후 재고(최대 3 유지): "
		<< workshop.GetStockByName("Healing Potion") << "\n";

	cout << "\n=== 최종 상태 ===\n";
	workshop.DisplayAllRecipes();
}

