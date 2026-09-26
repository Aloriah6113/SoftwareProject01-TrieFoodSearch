#include "Food.h"

using std::string;

Food::Food(
    const string& foodId, 
    const string& foodName, 
    const string& category, 
    const string& ingredients, 
    const string& recipe, 
    const string& allergyInfo, 
    const string& imageUrl
)
    : foodId(foodId),
      foodName(foodName),
      category(category),
      ingredients(ingredients),
      recipe(recipe),
      allergyInfo(allergyInfo),
      imageUrl(imageUrl)
{
}

string Food::getFoodId() const {
    return foodId;
}
string Food::getFoodName() const {
    return foodName;
}
string Food::getCategory() const {
    return category;
}
string Food::getIngredients() const {
    return ingredients;
}
string Food::getRecipe() const {
    return recipe;
}
string Food::getAllergyInfo() const {
    return allergyInfo;
}
string Food::getImageUrl() const {
    return imageUrl;
}

// void Food::getDetails() {}
