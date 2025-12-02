#pragma once
#include <string>

class Monster {
private:
    int hp;
    std::string name;
    int damage;
    std::string description;

public:
    Monster();
    Monster(int hp, const std::string& name, int damage, const std::string& description);
    ~Monster();

    std::string getName() const;
    int getHp() const;
    int getDamage() const;
    std::string getDescription() const;

    void setName(const std::string& name);
    void setHp(int hp);
    void setDamage(int damage);
    void setDescription(const std::string& description);

    void monstr_info() const;
    bool isAlive() const;
    void takeDamage(int amount);
};
