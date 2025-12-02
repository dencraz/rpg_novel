#include "Monster.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
using namespace utils;
using namespace utils::color;

// Вспомогательная функция (твоя)
bool isValidName_Monster(const string& name) {
    if (name.empty() || name.length() > 50) return false;
    return true;
}

Monster::Monster()
    : hp(100), maxHp(100), name("Test1"), minDamage(15), maxDamage(20), description("Test1"), isBoss(false) {
}

// Твой старый конструктор (для обычных монстров)
Monster::Monster(int hp, const string& name, int damage, const string& description)
    : hp(hp), maxHp(hp), name(name), minDamage(damage - 5), maxDamage(damage), description(description), isBoss(false) {
    if (minDamage < 0) minDamage = 0;
}

// Конструктор для БОССА
Monster::Monster(int hp, const string& name, int minDmg, int maxDmg, const string& description, bool isBoss)
    : hp(hp), maxHp(hp), name(name), minDamage(minDmg), maxDamage(maxDmg), description(description), isBoss(isBoss) {
}

Monster::~Monster() {}

string Monster::getName() const { return name; }
int Monster::getHp() const { return hp; }
int Monster::getCurrentHP() const { return hp; }
int Monster::getMaxHP() const { return maxHp; }

// Теперь getDamage возвращает случайное число для вариативности
int Monster::getDamage() const {
    if (minDamage >= maxDamage) return maxDamage;
    return utils::random(minDamage, maxDamage);
}

int Monster::getMinDamage() const { return minDamage; }
int Monster::getMaxDamage() const { return maxDamage; }
string Monster::getDescription() const { return description; }
bool Monster::getIsBoss() const { return isBoss; }

void Monster::setName(const string& name) {
    if (isValidName_Monster(name)) this->name = name;
    else this->name = "Безымянный";
}

void Monster::setHp(int hp) {
    if (hp >= 0 && hp <= 10000) {
        this->hp = hp;
        this->maxHp = hp; // Обновляем и максимум
    }
    else {
        this->hp = 100;
        this->maxHp = 100;
    }
}

void Monster::setDamage(int damage) {
    if (damage >= 0 && damage <= 1000) {
        this->maxDamage = damage;
        this->minDamage = damage - 5; // Делаем небольшой разброс автоматически
        if (this->minDamage < 0) this->minDamage = 0;
    }
    else {
        this->maxDamage = 20;
    }
}

void Monster::setDescription(const string& description) {
    if (!description.empty() && description.length() <= 200) {
        this->description = description;
    }
    else {
        this->description = "Без описания";
    }
}

void Monster::monstr_info() const {
    cout << (isBoss ? red : yellow) << "Имя: " << name << none << endl;
    cout << "Описание: " << description << endl;
    cout << "Здоровье: " << hp << "/" << maxHp << " HP" << endl;
    cout << "Урон: " << minDamage << "-" << maxDamage << endl;
}

bool Monster::isAlive() const {
    return hp > 0;
}

void Monster::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Monster::heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
}
