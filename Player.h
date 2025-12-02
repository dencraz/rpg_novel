#pragma once
#include <string>
#include <vector>
#include "Item.h"

class Monster; // Предварительное объявление

class Player {
private:
    std::string name;
    int age;
    int maxHP;
    int currentHP;
    int maxMana;
    int currentMana;
    int level;
    int gold;
    std::vector<Item> inventory;
    int maxInventorySize;

    void initializeStarterItems();

public:
    Player(std::string name = "", int age = 0, int maxHP = 100, int currentHP = 100,
        int maxMana = 50, int currentMana = 50, int level = 1, int gold = 0, int maxInventorySize = 10);

    // Геттеры
    std::string getName() const;
    int getAge() const;
    int getMaxHP() const;
    int getCurrentHP() const;
    int getMaxMana() const;
    int getCurrentMana() const;
    int getLevel() const;
    int getGold() const;
    int getInventorySize() const { return inventory.size(); }
    const std::vector<Item>& getInventory() const { return inventory; }

    // Сеттеры
    void setName(const std::string& newName);
    void setAge(int newAge);
    void setMaxHP(int newMaxHP);
    void setCurrentHP(int newCurrentHP);
    void setMaxMana(int newMaxMana);
    void setCurrentMana(int newCurrentMana);
    void setLevel(int newLevel);
    void setGold(int newGold);

    // Игровые методы
    void takeDamage(int damage);
    void heal(int amount);
    void useMana(int amount);
    void restoreMana(int amount);
    void addGold(int amount);
    void spendGold(int amount);
    void levelUp();
    bool isAlive() const;
    void displayPlayer() const;

    // Инвентарь
    bool addItem(const Item& item);
    bool removeItem(const std::string& itemName, int quantity);
    bool hasItem(const std::string& itemName) const;
    Item* findItem(const std::string& itemName);
    void displayInventory() const;
    void useItem(int itemIndex);
    void showProfile(Player* player);

    // Боевая система (НОВЫЙ МЕТОД)
    void battle(Monster* enemy);

    // Статические методы создания
    static Player generateRandom();
    static Player createManual();
};
