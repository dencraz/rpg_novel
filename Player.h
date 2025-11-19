#pragma once

#include <string>

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

public:
   
    Player(std::string name = "", int age = 0, int maxHP = 100,
        int currentHP = 100, int maxMana = 50, int currentMana = 50,
        int level = 1, int gold = 0);


    std::string getName() const;
    int getAge() const;
    int getMaxHP() const;
    int getCurrentHP() const;
    int getMaxMana() const;
    int getCurrentMana() const;
    int getLevel() const;
    int getGold() const;


    void setName(const std::string& newName);
    void setAge(int newAge);
    void setMaxHP(int newMaxHP);
    void setCurrentHP(int newCurrentHP);
    void setMaxMana(int newMaxMana);
    void setCurrentMana(int newCurrentMana);
    void setLevel(int newLevel);
    void setGold(int newGold);

  
    void takeDamage(int damage);
    void heal(int amount);
    void useMana(int amount);
    void restoreMana(int amount);
    void addGold(int amount);
    void spendGold(int amount);
    void levelUp();
    bool isAlive() const;
    void displayPlayer() const;

   
    static Player generateRandom();
    static Player createManual();
};
