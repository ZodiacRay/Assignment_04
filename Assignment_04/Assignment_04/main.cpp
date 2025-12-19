// Assignment_04.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "AlchemyWorkshop.h"
#include "PotionRecipe.h"
#include "Potion.h"
#include "StockManager.h"

#include <iostream>
using namespace std;


int main()
{
    AlchemyWorkshop* Shop = new AlchemyWorkshop();

    Shop->addRecipe("APotion", { "A","B","C" });
    Shop->addRecipe("BPotion", { "D","E","F" });
    Shop->addRecipe("CPotion", { "G","H","I" });

    PotionRecipe* foundArecipe = Shop->searchRecipeByName("APotion");
    cout << foundArecipe->getName() << "\n";
        
    for (string ing : foundArecipe->getIngredients())
    {
        cout << ing << " "; 
    }
    cout << '\n';

    for (PotionRecipe* foundrecipe : Shop->searchRecipeByIngredient("E"))
    {
       cout << foundrecipe->getName() << " ";
    }

    cout << '\n'; 
}

