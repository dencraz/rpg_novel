#include "Player.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string> 
#include "utils.h"

using namespace std;
using namespace utils;
using namespace utils::color;

std::string getAgeString(int age) {
    std::string result = std::to_string(age);

    if (age % 100 >= 11 && age % 100 <= 14) {
        return result + " лет";
    }

    int lastDigit = age % 10;

    if (lastDigit == 1) {
        return result + " год";
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {
        return result + " года";
    }
    else {
        return result + " лет";
    }
}

Player::Player(std::string name, int age, int maxHP, int currentHP,
    int maxMana, int currentMana, int level, int gold, int maxInventorySize)
    : name(name), age(age), maxHP(maxHP), currentHP(currentHP),
    maxMana(maxMana), currentMana(currentMana), level(level),
    gold(gold), maxInventorySize(maxInventorySize) {
    initializeStarterItems();
}

void Player::initializeStarterItems() {
    inventory.clear();

    inventory.push_back(Item("Малое зелье лечения", ItemType::POTION, 50,
        "Восстанавливает 30 HP", 5, 30, 0));

    inventory.push_back(Item("Среднее зелье лечения", ItemType::POTION, 100,
        "Восстанавливает 60 HP", 3, 60, 0));

    inventory.push_back(Item("Большое зелье лечения", ItemType::POTION, 150,
        "Восстанавливает 100 HP", 2, 100, 0));

    inventory.push_back(Item("Малое зелье маны", ItemType::POTION, 40,
        "Восстанавливает 25 маны", 5, 0, 25));

    inventory.push_back(Item("Среднее зелье маны", ItemType::POTION, 80,
        "Восстанавливает 50 маны", 3, 0, 50));

    inventory.push_back(Item("Большое зелье маны", ItemType::POTION, 120,
        "Восстанавливает 75 маны", 2, 0, 75));
}

std::string Player::getName() const { return name; }
int Player::getAge() const { return age; }
int Player::getMaxHP() const { return maxHP; }
int Player::getCurrentHP() const { return currentHP; }
int Player::getMaxMana() const { return maxMana; }
int Player::getCurrentMana() const { return currentMana; }
int Player::getLevel() const { return level; }
int Player::getGold() const { return gold; }

void Player::setName(const std::string& newName) { name = newName; }
void Player::setAge(int newAge) { age = newAge; }
void Player::setMaxHP(int newMaxHP) { maxHP = newMaxHP; }

void Player::setCurrentHP(int newCurrentHP) {
    currentHP = (newCurrentHP > maxHP) ? maxHP : newCurrentHP;
    currentHP = (currentHP < 0) ? 0 : currentHP;
}

void Player::setMaxMana(int newMaxMana) { maxMana = newMaxMana; }

void Player::setCurrentMana(int newCurrentMana) {
    currentMana = (newCurrentMana > maxMana) ? maxMana : newCurrentMana;
    currentMana = (currentMana < 0) ? 0 : currentMana;
}

void Player::setLevel(int newLevel) { level = newLevel; }
void Player::setGold(int newGold) { gold = newGold; }

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

void Player::addGold(int amount) { gold += amount; }

void Player::spendGold(int amount) {
    gold -= amount;
    if (gold < 0) gold = 0;
}

void Player::levelUp() { level++; }
bool Player::isAlive() const { return currentHP > 0; }

void Player::displayPlayer() const {
    std::cout << cyan << "+----------------------------------------------------------+" << none << std::endl;
    std::cout << cyan << "|" << yellow << "            *** ИНФОРМАЦИЯ О ПЕРСОНАЖЕ ***                " << cyan << "|" << none << std::endl;
    std::cout << cyan << "+----------------------------------------------------------+" << none << std::endl;

    std::cout << cyan << "| " << green << "Имя: " << yellow << std::setw(20) << std::left << name
        << cyan << string(31 - name.length(), ' ') << "|" << none << std::endl;

    std::string ageStr = getAgeString(age);
    std::cout << cyan << "| " << green << "Возраст: " << yellow << ageStr
        << cyan << string(44 - ageStr.length(), ' ') << "|" << none << std::endl;

    std::cout << cyan << "| " << green << "HP: " << yellow << currentHP << "/" << maxHP
        << cyan << string(46 - to_string(currentHP).length() - to_string(maxHP).length(), ' ') << "|" << none << std::endl;
    std::cout << cyan << "| " << green << "Мана: " << yellow << currentMana << "/" << maxMana
        << cyan << string(44 - to_string(currentMana).length() - to_string(maxMana).length(), ' ') << "|" << none << std::endl;
    std::cout << cyan << "| " << green << "Уровень: " << yellow << level
        << cyan << string(43 - to_string(level).length(), ' ') << "|" << none << std::endl;
    std::cout << cyan << "| " << green << "Золото: " << yellow << gold
        << cyan << string(44 - to_string(gold).length(), ' ') << "|" << none << std::endl;
    std::cout << cyan << "| " << green << "Предметов в инвентаре: " << yellow << inventory.size()
        << cyan << string(30 - to_string(inventory.size()).length(), ' ') << "|" << none << std::endl;
    std::cout << cyan << "+----------------------------------------------------------+" << none << std::endl;
}

bool Player::addItem(const Item& item) {
    for (auto& invItem : inventory) {
        if (invItem.getName() == item.getName()) {
            invItem.addQuantity(item.getQuantity());
            std::cout << green << "Добавлено: " << item.getName()
                << " x" << item.getQuantity() << none << std::endl;
            return true;
        }
    }

    if (inventory.size() >= maxInventorySize) {
        std::cout << red << "Инвентарь переполнен!" << none << std::endl;
        return false;
    }

    inventory.push_back(item);
    std::cout << green << "Получен предмет: " << item.getName()
        << " x" << item.getQuantity() << none << std::endl;
    return true;
}

bool Player::removeItem(const std::string& itemName, int quantity) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->getName() == itemName) {
            if (it->getQuantity() > quantity) {
                it->setQuantity(it->getQuantity() - quantity);
                return true;
            }
            else if (it->getQuantity() == quantity) {
                inventory.erase(it);
                return true;
            }
            else {
                std::cout << red << "Недостаточно предметов!" << none << std::endl;
                return false;
            }
        }
    }
    std::cout << red << "Предмет не найден!" << none << std::endl;
    return false;
}

bool Player::hasItem(const std::string& itemName) const {
    for (const auto& item : inventory) {
        if (item.getName() == itemName) {
            return true;
        }
    }
    return false;
}

Item* Player::findItem(const std::string& itemName) {
    for (auto& item : inventory) {
        if (item.getName() == itemName) {
            return &item;
        }
    }
    return nullptr;
}

void Player::displayInventory() const {
    system("cls");

    std::cout << cyan << "+------------------------------------------------------------+" << none << std::endl;
    std::cout << cyan << "|" << yellow << "              ИНВЕНТАРЬ ИГРОКА                            " << cyan << "|" << none << std::endl;
    std::cout << cyan << "+------------------------------------------------------------+" << none << std::endl;
    std::cout << cyan << "| " << green << "Золото: " << yellow << std::setw(6) << gold
        << cyan << "                    Слотов: " << yellow << inventory.size()
        << "/" << maxInventorySize << cyan << "          |" << none << std::endl;
    std::cout << cyan << "+------------------------------------------------------------+" << none << std::endl;

    if (inventory.empty()) {
        std::cout << cyan << "|" << yellow << "              Инвентарь пуст                            "
            << cyan << "|" << none << std::endl;
    }
    else {
        std::cout << cyan << "| №  | " << yellow << "Название" << cyan << "                  | "
            << yellow << "Кол-во" << cyan << " | " << yellow << "Эффект" << cyan << "       |" << none << std::endl;
        std::cout << cyan << "+----+------------------------+--------+-------------+" << none << std::endl;

        for (size_t i = 0; i < inventory.size(); ++i) {
            const auto& item = inventory[i];

            std::string effect = "";
            if (item.getHealAmount() > 0) {
                effect = "HP +" + std::to_string(item.getHealAmount());
            }
            else if (item.getManaAmount() > 0) {
                effect = "Мана +" + std::to_string(item.getManaAmount());
            }

            std::cout << cyan << "| " << yellow << std::setw(2) << (i + 1)
                << cyan << " | " << green << std::setw(24) << std::left << item.getName()
                << cyan << " | " << yellow << std::setw(6) << std::right << item.getQuantity()
                << cyan << " | " << magenta << std::setw(12) << std::left << effect
                << cyan << " |" << none << std::endl;
        }
    }

    std::cout << cyan << "+------------------------------------------------------------+" << none << std::endl;
}

void Player::useItem(int itemIndex) {
    if (itemIndex < 0 || itemIndex >= inventory.size()) {
        std::cout << red << "Неверный номер предмета!" << none << std::endl;
        return;
    }

    Item& item = inventory[itemIndex];

    if (item.getType() == ItemType::POTION) {
        if (item.getHealAmount() > 0) {
            int oldHP = currentHP;
            heal(item.getHealAmount());
            int healedAmount = currentHP - oldHP;
            std::cout << green << "Восстановлено " << healedAmount << " HP!" << none << std::endl;
        }

        if (item.getManaAmount() > 0) {
            int oldMana = currentMana;
            restoreMana(item.getManaAmount());
            int restoredAmount = currentMana - oldMana;
            std::cout << cyan << "Восстановлено " << restoredAmount << " маны!" << none << std::endl;
        }

        std::string itemName = item.getName();
        removeItem(itemName, 1);
        std::cout << yellow << "Использован предмет: " << itemName << none << std::endl;
    }
    else {
        std::cout << red << "Этот предмет нельзя использовать!" << none << std::endl;
    }
}

Player Player::generateRandom() {
    bool confirmed = false;
    Player player;

    while (!confirmed) {
        system("cls");

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

        std::cout << magenta << "+----------------------------------------------------------+" << none << std::endl;
        std::cout << magenta << "|" << yellow << "           *** СЛУЧАЙНАЯ ГЕНЕРАЦИЯ ***                    " << magenta << "|" << none << std::endl;
        std::cout << magenta << "+----------------------------------------------------------+" << none << std::endl;
        wait(1);

        player.displayPlayer();

        std::cout << green << "\n+----------------------------------------------------------+" << none << std::endl;
        std::cout << green << "|  Получено 6 типов стартовых зелий!                       |" << none << std::endl;
        std::cout << green << "+----------------------------------------------------------+" << none << std::endl;

        std::cout << blue << "\nПодтвердить создание персонажа? (1 - Да, 0 - Нет): " << none;
        int confirm = rightValue();

        if (confirm == 1) {
            confirmed = true;
            std::cout << green << "Персонаж создан!" << none << std::endl;
            wait(1);
        }
        else {
            std::cout << yellow << "Создание отменено. Генерируем нового персонажа..." << none << std::endl;
            wait(1);
        }
    }

    return player;
}

Player Player::createManual() {
    std::string name;
    int age;
    bool confirmed = false;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (!confirmed) {
        system("cls");

        std::cout << magenta << "+----------------------------------------------------------+" << none << std::endl;
        std::cout << magenta << "|" << yellow << "            *** РУЧНОЕ СОЗДАНИЕ ***                       " << magenta << "|" << none << std::endl;
        std::cout << magenta << "+----------------------------------------------------------+" << none << std::endl;
        std::cout << std::endl;

        rightName(name, "Введите имя (на англ): ", 2, 30);

        do {
            std::cout << blue << "Введите возраст (положительное число): " << none;
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

        std::cout << std::endl;
        std::cout << cyan << "+----------------------------------------------------------+" << none << std::endl;
        std::cout << cyan << "|" << yellow << "              ВВЕДЁННЫЕ ДАННЫЕ                            " << cyan << "|" << none << std::endl;
        std::cout << cyan << "+----------------------------------------------------------+" << none << std::endl;
        player.displayPlayer();

        std::cout << green << "\n+----------------------------------------------------------+" << none << std::endl;
        std::cout << green << "|  Получено 6 типов стартовых зелий!                       |" << none << std::endl;
        std::cout << green << "+----------------------------------------------------------+" << none << std::endl;

        std::cout << blue << "\nПодтвердить создание персонажа? (1 - Да, 0 - Нет): " << none;
        int confirm = rightValue();

        if (confirm == 1) {
            confirmed = true;
            wait(1);
            std::cout << green << "Персонаж создан!" << none << std::endl;
            wait(2);
            return player;
        }
        else {
            std::cout << yellow << "Повторите ввод данных..." << none << std::endl;
            wait(1);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return Player();
}
void Player::showProfile(Player* player) {
    if (!player) {
        print("Ошибка: персонаж не найден!", textSpeed, red);
        wait(2);
        return;
    }

    int choice;
    do {
        system("cls");

        cout << magenta << "+----------------------------------------------------------+" << none << endl;
        cout << magenta << "|" << yellow << "                   *** ПРОФИЛЬ ***                        " << magenta << "|" << none << endl;
        cout << magenta << "+----------------------------------------------------------+" << none << endl;
        cout << endl;

        player->displayPlayer();

        cout << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << yellow << "[1]" << cyan << " Показать инвентарь" << string(35, ' ') << "|" << none << endl;
        cout << cyan << "| " << red << "[0]" << cyan << " Вернуться в меню" << string(37, ' ') << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        cout << blue << "Ваш выбор: " << none;
        choice = rightValue();

        switch (choice) {
        case 1:
            player->displayInventory();
            cout << endl;
            print("Нажмите Enter для продолжения...", textSpeed, gray);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        case 0:
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }
    } while (choice != 0);
}
bool Player::openInventoryMenu() {
    // Если инвентарь пуст
    if (inventory.empty()) {
        std::cout << red << "Инвентарь пуст!" << none << std::endl;
        utils::wait(2);
        return false; // Ход не потрачен
    }

    int selectedIndex = 0;
    bool inInventory = true;
    bool itemUsed = false; // Флаг: использовали ли мы что-то?

    while (inInventory) {
        system("cls");

        cout << green << "+----------------------------------------------------------+" << none << endl;
        cout << green << "| HP: " << yellow << getCurrentHP() << "/" << getMaxHP()
            << green << " | Мана: " << cyan << getCurrentMana() << "/" << getMaxMana()
            << green << " | Золото: " << yellow << getGold() << green << "                     |" << none << endl;
        cout << green << "+----------------------------------------------------------+" << none << endl;
        cout << endl;

        cout << cyan << "+------------------------------------------------------------+" << none << endl;
        cout << cyan << "|          " << yellow << "ИНВЕНТАРЬ (используйте w/s/e/q)" << cyan
            << "                  |" << none << endl;
        cout << cyan << "+------------------------------------------------------------+" << none << endl;

        for (size_t i = 0; i < inventory.size(); ++i) {
            const auto& item = inventory[i];

            string effect = "";
            if (item.getHealAmount() > 0) {
                effect = "HP +" + to_string(item.getHealAmount());
            }
            else if (item.getManaAmount() > 0) {
                effect = "Мана +" + to_string(item.getManaAmount());
            }

            if (i == selectedIndex) {
                cout << cyan << "| >> " << green << item.getName()
                    << yellow << " x" << item.getQuantity()
                    << magenta << " [" << effect << "]" << cyan;
            }
            else {
                cout << cyan << "|    " << none << item.getName()
                    << yellow << " x" << item.getQuantity()
                    << gray << " [" << effect << "]" << cyan;
            }

            int spaces = 60 - item.getName().length() - to_string(item.getQuantity()).length() - effect.length() - 10;
            if (spaces < 0) spaces = 0;
            cout << string(spaces, ' ') << "|" << none << endl;
        }

        cout << cyan << "+------------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << yellow << "w/s" << cyan << " - Выбор  |  "
            << yellow << "e" << cyan << " - Использовать  |  "
            << yellow << "q" << cyan << " - Закрыть       |" << none << endl;
        cout << cyan << "+------------------------------------------------------------+" << none << endl;

        cout << "Ваш выбор: ";

        char invKey;
        cin >> invKey;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (invKey) {
        case 'w':
        case 'W':
            if (selectedIndex > 0) {
                selectedIndex--;
            }
            break;

        case 's':
        case 'S':
            if (selectedIndex < inventory.size() - 1) {
                selectedIndex++;
            }
            break;

        case 'e':
        case 'E':
            // 1. Используем предмет
            useItem(selectedIndex);

            // 2. ВАЖНО: Говорим игре, что предмет был использован!
            itemUsed = true;

            wait(2);

            // 3. Проверки на пустой инвентарь (чтобы не было вылета)
            if (getInventorySize() == 0) {
                print("Инвентарь пуст!", textSpeed, yellow);
                wait(1);
                inInventory = false;
            }
            else if (selectedIndex >= getInventorySize()) {
                selectedIndex = getInventorySize() - 1;
            }
            break;

        case 'q':
        case 'Q':
            inInventory = false;
            break;

        default:
            print("Неверная клавиша!", textSpeed, red);
            wait(1);
            break;
        }
    }

    return itemUsed; // Возвращаем true, если потратили ход
}
