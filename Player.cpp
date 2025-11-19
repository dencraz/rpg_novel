#include "Player.h"
#include <iostream>
#include <limits>
#include "utils.h"

using namespace utils;
using namespace utils::color;


Player::Player(std::string name, int age, int maxHP, int currentHP,
    int maxMana, int currentMana, int level, int gold)
    : name(name), age(age), maxHP(maxHP), currentHP(currentHP),
    maxMana(maxMana), currentMana(currentMana), level(level), gold(gold) {
}


std::string Player::getName() const {
    return name;
}

int Player::getAge() const {
    return age;
}

int Player::getMaxHP() const {
    return maxHP;
}

int Player::getCurrentHP() const {
    return currentHP;
}

int Player::getMaxMana() const {
    return maxMana;
}

int Player::getCurrentMana() const {
    return currentMana;
}

int Player::getLevel() const {
    return level;
}

int Player::getGold() const {
    return gold;
}


void Player::setName(const std::string& newName) {
    name = newName;
}

void Player::setAge(int newAge) {
    age = newAge;
}

void Player::setMaxHP(int newMaxHP) {
    maxHP = newMaxHP;
}

void Player::setCurrentHP(int newCurrentHP) {
    currentHP = (newCurrentHP > maxHP) ? maxHP : newCurrentHP;
    currentHP = (currentHP < 0) ? 0 : currentHP;
}

void Player::setMaxMana(int newMaxMana) {
    maxMana = newMaxMana;
}

void Player::setCurrentMana(int newCurrentMana) {
    currentMana = (newCurrentMana > maxMana) ? maxMana : newCurrentMana;
    currentMana = (currentMana < 0) ? 0 : currentMana;
}

void Player::setLevel(int newLevel) {
    level = newLevel;
}

void Player::setGold(int newGold) {
    gold = newGold;
}


void Player::takeDamage(int damage) {
    currentHP -= damage;
    if (currentHP < 0) currentHP = 0;
}

void Player::heal(int amount) {
    currentHP += amount;
    if (currentHP > maxHP) currentHP = maxHP;
}

void Player::useMana(int amount) {
    currentMana -= amount;
    if (currentMana < 0) currentMana = 0;
}

void Player::restoreMana(int amount) {
    currentMana += amount;
    if (currentMana > maxMana) currentMana = maxMana;
}

void Player::addGold(int amount) {
    gold += amount;
}

void Player::spendGold(int amount) {
    gold -= amount;
    if (gold < 0) gold = 0;
}

void Player::levelUp() {
    level++;
}

bool Player::isAlive() const {
    return currentHP > 0;
}


void Player::displayPlayer() const {
    std::cout << "=== Информация о персонаже ===" << std::endl;
    std::cout << "Имя: " << name << std::endl;
    std::cout << "Возраст: " << age << " лет" << std::endl;
    std::cout << "HP: " << currentHP << "/" << maxHP << std::endl;
    std::cout << "Мана: " << currentMana << "/" << maxMana << std::endl;
    std::cout << "Уровень: " << level << std::endl;
    std::cout << "Золото: " << gold << std::endl;
    std::cout << "==============================" << std::endl;
}


Player Player::generateRandom() {
    bool confirmed = false;
    Player player;

    while (!confirmed) {
        // Массив имён
        std::string names[] = {
            "Артур", "Владимир", "Дмитрий", "Игорь", "Максим",
            "Никита", "Олег", "Петр", "Роман", "Сергей"
        };

        
        std::string randomName = names[random(0, 9)];
        int randomAge = random(18, 50);
        int randomMaxHP = random(90, 100);
        int randomMaxMana = random(30, 100);
        int level = 1;
        int randomGold = random(200, 500);

        player = Player(randomName, randomAge, randomMaxHP, randomMaxHP,
            randomMaxMana, randomMaxMana, level, randomGold);

        wait(2);
        player.displayPlayer();

        // Запрос подтверждения с проверкой
        std::cout << "\nПодтвердить создание персонажа? (1 - Да, 0 - Нет): ";
        int confirm = rightValue();

        if (confirm == 1) {
            confirmed = true;
            std::cout << "Персонаж создан!" << std::endl;
        }
        else {
            std::cout << "Создание отменено. Генерируем нового персонажа...\n" << std::endl;
            wait(1);
        }
    }

    return player;
}


Player Player::createManual() {
    std::string name;
    int age, maxHP;
    bool confirmed = false;

   
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (!confirmed) {
        std::cout << "\n=== Ручное создание персонажа ===" << std::endl;

        std::string name;
        rightName(name, "Введите имя: ", 2, 30);


        do {
            std::cout << "Введите возраст (положительное число): ";
            age = rightValue();
            if (age <= 0) {
                print("Ошибка! Возраст должен быть больше 0", textSpeed, red);
            }
        } while (age <= 0);



        int maxHP = 100;

        int maxMana = 100;
        int level = 1;
        int gold = 300;

        
        Player player(name, age, maxHP, maxHP, maxMana, maxMana, level, gold);

        
        std::cout << "\n=== Введённые данные ===" << std::endl;
        player.displayPlayer();

        
        std::cout << "\nПодтвердить создание персонажа? (1 - Да, 0 - Нет): ";
        int confirm = rightValue();

        if (confirm == 1) {
            confirmed = true;
            wait(1);
            std::cout << "Персонаж создан!" << std::endl;
            wait(3);
            return player;
        }
        else {
            std::cout << "Повторите ввод данных...\n" << std::endl;
            wait(1);
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }


    return Player();
}
