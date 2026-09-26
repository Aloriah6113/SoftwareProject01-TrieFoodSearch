#include "Food.h"

using std::string;

Food::Food(
    const string& foodId,
    const string& foodName,
    const string& category,
    const string& subcategory,
    const string& weight,
    const string& recipe,
    const string& allergyInfo,
    const string& ingredients,
    const string& imageUrl
)
    : foodId(foodId),
    foodName(foodName),
    category(category),
    subcategory(subcategory),
    weight(weight),
    recipe(recipe),
    allergyInfo(allergyInfo),
    ingredients(ingredients),
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

string Food::getSubcategory() const {
    return subcategory;
}

string Food::getWeight() const {
    return weight;
}

string Food::getRecipe() const {
    return recipe;
}

string Food::getAllergyInfo() const {
    return allergyInfo;
}

string Food::getIngredients() const {
    return ingredients;
}

string Food::getImageUrl() const {
    return imageUrl;
}