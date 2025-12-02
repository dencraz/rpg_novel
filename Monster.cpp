#include "Monster.h"
#include "utils.h"
#include <limits>
#include <cstdlib>
#include <ctype.h>
#include <iostream>
#include <string>

using namespace std;
using namespace utils;
using namespace utils::color;

bool isValidName_Monster(const string& name) {
    if (name.empty() || name.length() > 50) return false;
    for (char c : name) {
        if (isalpha(c)) return true;
    }
    return false;
}

Monster::Monster() : hp(100), name("Test1"), damage(20), description("Test1") {}

Monster::Monster(int hp, const string& name, int damage, const string& description)
    : hp(hp), name(name), damage(damage), description(description) {
}

Monster::~Monster() {}

string Monster::getName() const { return name; }
int Monster::getHp() const { return hp; }
int Monster::getDamage() const { return damage; }
string Monster::getDescription() const { return description; }

void Monster::setName(const string& name) {
    if (isValidName_Monster(name)) {
        this->name = name;
    }
    else {
        cout << "Ошибка: имя должно содержать буквы" << endl;
        this->name = "Безымянный";
    }
}

void Monster::setHp(int hp) {
    if (hp >= 0 && hp <= 10000) {
        this->hp = hp;
    }
    else {
        cout << "HP должно быть в диапазоне 0-10000" << endl;
        this->hp = 100;
    }
}

void Monster::setDamage(int damage) {
    if (damage >= 0 && damage <= 1000) {
        this->damage = damage;
    }
    else {
        cout << "Урон должен быть в диапазоне 0-1000" << endl;
        this->damage = 20;
    }
}

void Monster::setDescription(const string& description) {
    if (!description.empty() && description.length() <= 200) {
        this->description = description;
    }
    else {
        cout << "Ошибка: описание не должно быть пустым и не более 200 символов!" << endl;
        this->description = "Без описания";
    }
}

void Monster::monstr_info() const {
    cout << "Имя: " << name << endl;
    cout << "Описание: " << description << endl;
    cout << "Здоровье: " << hp << " HP" << endl;
    cout << "Урон: " << damage << endl;
}

bool Monster::isAlive() const {
    return hp > 0;
}

void Monster::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}
