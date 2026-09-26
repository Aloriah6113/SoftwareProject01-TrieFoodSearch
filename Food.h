#pragma once

#include <string>

class Food {
public:
    Food(
        const std::string& foodId,
        const std::string& foodName,
        const std::string& category,
        const std::string& subcategory,
        const std::string& weight,
        const std::string& recipe,
        const std::string& allergyInfo,
        const std::string& ingredients,
        const std::string& imageUrl
    );

    std::string getFoodId() const;
    std::string getFoodName() const;
    std::string getCategory() const;
    std::string getSubcategory() const;
    std::string getWeight() const;
    std::string getRecipe() const;
    std::string getAllergyInfo() const;
    std::string getIngredients() const;
    std::string getImageUrl() const;

private:
    std::string foodId;
    std::string foodName;
    std::string category;
    std::string subcategory;
    std::string weight;
    std::string recipe;
    std::string allergyInfo;
    std::string ingredients;
    std::string imageUrl;
};