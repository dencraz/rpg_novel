#pragma once
#include <string>

enum class ItemType {
    WEAPON,
    ARMOR,
    POTION,
    FOOD,
    QUEST,
    MISC
};

class Item {
private:
    std::string name;
    ItemType type;
    int value;
    int quantity;
    std::string description;
    int healAmount;
    int manaAmount;

public:
    Item(const std::string& name, ItemType type, int value,
        const std::string& description, int quantity = 1,
        int healAmount = 0, int manaAmount = 0);

    std::string getName() const { return name; }
    ItemType getType() const { return type; }
    int getValue() const { return value; }
    int getQuantity() const { return quantity; }
    std::string getDescription() const { return description; }
    int getHealAmount() const { return healAmount; }
    int getManaAmount() const { return manaAmount; }

    void setQuantity(int q) { quantity = q; }
    void addQuantity(int amount) { quantity += amount; }

    std::string getTypeString() const;
};
