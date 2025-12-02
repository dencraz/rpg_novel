#pragma once
#include <string>

class Monster {
private:
    int hp;
    int maxHp;      // Нужно для полоски HP босса
    std::string name;
    int minDamage;  // Мин. урон
    int maxDamage;  // Макс. урон (используется как основной damage в старом коде)
    std::string description;
    bool isBoss;    // Флаг босса

public:
    Monster();
    // Обновленный конструктор, совместимый со старым кодом (через перегрузку или параметры по умолчанию)
    Monster(int hp, const std::string& name, int damage, const std::string& description);
    // Конструктор для БОССА (расширенный)
    Monster(int hp, const std::string& name, int minDmg, int maxDmg, const std::string& description, bool isBoss);
    ~Monster();

    std::string getName() const;
    int getHp() const;        // Оставил твое старое название
    int getCurrentHP() const; // Алиас для удобства
    int getMaxHP() const;     // Новое
    int getDamage() const;    // Возвращает средний или случайный урон
    int getMinDamage() const;
    int getMaxDamage() const;
    std::string getDescription() const;
    bool getIsBoss() const;

    void setName(const std::string& name);
    void setHp(int hp);
    void setDamage(int damage);
    void setDescription(const std::string& description);

    void monstr_info() const;
    bool isAlive() const;
    void takeDamage(int amount);
    void heal(int amount); // Новое
};
