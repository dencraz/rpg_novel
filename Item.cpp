#include "Item.h"

Item::Item(const std::string& name, ItemType type, int value,
    const std::string& description, int quantity,
    int healAmount, int manaAmount)
    : name(name), type(type), value(value), description(description),
    quantity(quantity), healAmount(healAmount), manaAmount(manaAmount) {
}

std::string Item::getTypeString() const {
    switch (type) {
    case ItemType::WEAPON: return "Оружие";
    case ItemType::ARMOR: return "Броня";
    case ItemType::POTION: return "Зелье";
    case ItemType::FOOD: return "Еда";
    case ItemType::QUEST: return "Квест";
    case ItemType::MISC: return "Разное";
    default: return "Неизвестно";
    }
}
