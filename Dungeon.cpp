#include "Dungeon.h"
#include "LocationMenu.h"
#include "Monster.h"
#include "Player.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits>

using namespace std;
using namespace utils;
using namespace utils::color;

Dungeon::Dungeon() : locationMenuPtr(nullptr), playerPtr(nullptr) {}

Dungeon::~Dungeon() {}

void Dungeon::setLocationMenu(LocationMenu* locMenu) {
    locationMenuPtr = locMenu;
}

void Dungeon::setPlayer(Player* player) {
    playerPtr = player;
}

string Dungeon::getDescription() const {
    return "Вы находитесь в пещере.";
}

void Dungeon::enter() {
    if (!playerPtr) {
        cout << red << "Ошибка: игрок не найден!" << none << endl;
        return;
    }

    if (!playerPtr->isAlive()) {
        system("cls");
        print("Вы воскрешаетесь у входа в пещеру...", textSpeed, yellow);
        playerPtr->setCurrentHP(playerPtr->getMaxHP());
        playerPtr->setCurrentMana(playerPtr->getMaxMana());
        wait(2);
    }

    int encounters = 5;
    int initialGold = playerPtr->getGold();

    for (int i = 1; i <= encounters && playerPtr->isAlive(); i++) {
        if (utils::random(1, 100) <= 20 && i < encounters) {
            int foundGold = utils::random(100, 500);
            playerPtr->addGold(foundGold);

            system("cls");
            cout << green << "HP: " << playerPtr->getCurrentHP() << "/" << playerPtr->getMaxHP()
                << " | Золото: " << playerPtr->getGold() << none << endl;
            print("*** ВСТРЕЧА " + to_string(i) + " ИЗ " + to_string(encounters) + " ***", textSpeed, yellow);
            print("Вы нашли сундук с сокровищами!", textSpeed, green);
            print("Внутри вы находите " + to_string(foundGold) + " золотых монет!", textSpeed, yellow);
            print("Всего золота: " + to_string(playerPtr->getGold()), textSpeed, cyan);
            wait(3);
        }
        else {
            system("cls");
            print("*** ВСТРЕЧА " + to_string(i) + " ИЗ " + to_string(encounters) + " ***", textSpeed, yellow);
            print("Вы встречаете противников!", textSpeed, red);
            wait(2);

            vector<Monster*> monsters;
            int monsterCount = (utils::random(1, 100) <= 50) ? 1 : 2;

            for (int j = 0; j < monsterCount; j++) {
                int monsterType = utils::random(1, 10);
                Monster* monster = nullptr;

                switch (monsterType) {
                case 1:
                    monster = new Monster(100, "Зомби", 15, "Медленный, но живучий мертвец");
                    break;
                case 2:
                    monster = new Monster(70, "Скелет", 18, "Костлявый воин с мечом");
                    break;
                case 3:
                    monster = new Monster(120, "Огр", 20, "Огромный и свирепый великан");
                    break;
                case 4:
                    monster = new Monster(60, "Гоблин", 12, "Мелкий, но хитрый разбойник");
                    break;
                case 5:
                    monster = new Monster(90, "Волк", 16, "Дикий хищник с острыми клыками");
                    break;
                case 6:
                    monster = new Monster(80, "Призрак", 14, "Бестелесная тень из прошлого");
                    break;
                case 7:
                    monster = new Monster(150, "Тролль", 22, "Регенерирующий каменный монстр");
                    break;
                case 8:
                    monster = new Monster(50, "Слизень", 10, "Ядовитая желеобразная масса");
                    break;
                case 9:
                    monster = new Monster(110, "Орк", 19, "Воинственный зеленокожий громила");
                    break;
                case 10:
                    monster = new Monster(85, "Вампир", 17, "Кровопийца, скрывающийся в тени");
                    break;
                }

                if (monster) {
                    monsters.push_back(monster);
                }
            }

            bool inBattle = true;

            while (inBattle && playerPtr->isAlive()) {
                system("cls");

                cout << green << "+----------------------------------------------------------+" << none << endl;
                cout << green << "| ИГРОК: " << yellow << playerPtr->getName() << green;
                cout << string(42 - playerPtr->getName().length(), ' ') << "|" << none << endl;
                cout << green << "| HP: " << yellow << playerPtr->getCurrentHP() << "/" << playerPtr->getMaxHP()
                    << green << " | Мана: " << cyan << playerPtr->getCurrentMana() << "/" << playerPtr->getMaxMana()
                    << green << " | Золото: " << yellow << playerPtr->getGold() << green << "              |" << none << endl;
                cout << green << "+----------------------------------------------------------+" << none << endl;
                cout << endl;

                vector<Monster*> aliveMonsters;
                for (auto* monster : monsters) {
                    if (monster->isAlive()) {
                        aliveMonsters.push_back(monster);
                    }
                }

                if (aliveMonsters.empty()) {
                    print("Все враги повержены! Вы победили!", textSpeed, green);
                    int goldReward = utils::random(50, 150);
                    playerPtr->addGold(goldReward);
                    print("Получено " + to_string(goldReward) + " золота!", textSpeed, yellow);
                    wait(2);
                    inBattle = false;
                    break;
                }

                cout << red << "=== ВРАГИ ===" << none << endl;
                for (size_t idx = 0; idx < aliveMonsters.size(); idx++) {
                    Monster* m = aliveMonsters[idx];
                    cout << yellow << "Монстр " << (idx + 1) << ": " << none << m->getName() << endl;
                    cout << cyan << "HP: " << red << m->getHp() << cyan << " | Урон: " << red << m->getDamage() << none << endl;
                    cout << gray << "Описание: " << m->getDescription() << none << endl;
                    cout << endl;
                }

                cout << cyan << "+------------------------------------------------------+" << none << endl;
                cout << cyan << "|  " << yellow << "[w] Атака" << cyan << "        "
                    << yellow << "[e] Инвентарь" << cyan << "        "
                    << yellow << "[q] Побег" << cyan << "     |" << none << endl;
                cout << cyan << "+------------------------------------------------------+" << none << endl;
                cout << "Ваш выбор: ";

                char key;
                cin >> key;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (key) {
                case 'w':
                case 'W':
                    if (!aliveMonsters.empty()) {
                        Monster* target = aliveMonsters[0];

                        int playerDamage = 25;
                        target->takeDamage(playerDamage);

                        print("Вы атакуете " + target->getName() + " и наносите " +
                            to_string(playerDamage) + " урона!", textSpeed, green);

                        if (!target->isAlive()) {
                            print(target->getName() + " повержен!", textSpeed, yellow);
                        }

                        bool allDead = true;
                        for (const auto& monster : monsters) {
                            if (monster->isAlive()) {
                                allDead = false;
                                break;
                            }
                        }

                        if (allDead) {
                            print("Все враги повержены! Вы победили!", textSpeed, green);
                            int goldReward = utils::random(50, 150);
                            playerPtr->addGold(goldReward);
                            print("Получено " + to_string(goldReward) + " золота!", textSpeed, yellow);
                            wait(2);
                            inBattle = false;
                            break;
                        }

                        for (const auto& monster : monsters) {
                            if (monster->isAlive()) {
                                int monsterDamage = monster->getDamage();
                                int randVal = utils::random(1, 100);
                                if (randVal <= 70) {
                                    playerPtr->takeDamage(monsterDamage);
                                    print("Вы получили " + to_string(monsterDamage) + " урона!", textSpeed, red);

                                    if (!playerPtr->isAlive()) {
                                        print("Вы пали в бою! Игра окончена.", textSpeed, bright_red);
                                        wait(2);
                                        break;
                                    }
                                }
                                else {
                                    print("Монстр промахнулся! Урон не получен.", textSpeed, green);
                                }
                            }
                        }
                    }
                    wait(2);
                    break;

                case 'e':
                case 'E':
                {
                    const auto& inventory = playerPtr->getInventory();

                    if (inventory.empty()) {
                        print("Инвентарь пуст!", textSpeed, red);
                        wait(2);
                        break;
                    }

                    int selectedIndex = 0;
                    bool inInventory = true;

                    while (inInventory) {
                        system("cls");

                        cout << green << "+----------------------------------------------------------+" << none << endl;
                        cout << green << "| HP: " << yellow << playerPtr->getCurrentHP() << "/" << playerPtr->getMaxHP()
                            << green << " | Мана: " << cyan << playerPtr->getCurrentMana() << "/" << playerPtr->getMaxMana()
                            << green << " | Золото: " << yellow << playerPtr->getGold() << green << "                     |" << none << endl;
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
                            playerPtr->useItem(selectedIndex);
                            wait(2);

                            if (playerPtr->getInventorySize() == 0) {
                                print("Инвентарь пуст!", textSpeed, yellow);
                                wait(1);
                                inInventory = false;
                            }
                            else if (selectedIndex >= playerPtr->getInventorySize()) {
                                selectedIndex = playerPtr->getInventorySize() - 1;
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
                }
                break;

                case 'q':
                case 'Q':
                {
                    int escapeChance = utils::random(1, 100);
                    if (escapeChance <= 20) {
                        print("Вам удалось сбежать из боя!", textSpeed, green);
                        wait(2);
                        inBattle = false;
                    }
                    else {
                        print("Попытка бегства не удалась! Монстры атакуют!", textSpeed, red);

                        for (const auto& monster : monsters) {
                            if (monster->isAlive()) {
                                int monsterDamage = monster->getDamage();
                                playerPtr->takeDamage(monsterDamage);
                                print("Вы получили " + to_string(monsterDamage) + " урона!", textSpeed, red);
                                if (!playerPtr->isAlive()) break;
                            }
                        }
                        wait(2);
                    }
                }
                break;

                default:
                    print("Используйте w (атака), e (инвентарь) или q (побег)", textSpeed, red);
                    wait(1);
                    break;
                }
            }

            for (Monster* monster : monsters) {
                delete monster;
            }
            monsters.clear();
        }
    }

    system("cls");

    if (!playerPtr->isAlive()) {
        print("*** ВАС ПОБЕДИЛИ ***", textSpeed, bright_red);
        print("Вы пали в бою...", textSpeed, red);
        playerPtr->setGold(initialGold);

        playerPtr->setCurrentHP(playerPtr->getMaxHP());
        playerPtr->setCurrentMana(playerPtr->getMaxMana());
    }
    else {
        print("*** ПОДЗЕМЕЛЬЕ ПРОЙДЕНО ***", textSpeed, green);
        print("Вы успешно прошли все встречи в подземелье!", textSpeed, none);

        int goldEarned = playerPtr->getGold() - initialGold;
        if (goldEarned > 0) {
            print("Вы заработали: " + to_string(goldEarned) + " золотых монет", textSpeed, yellow);
        }

        int currentLevel = playerPtr->getLevel();
        playerPtr->levelUp();
        int newLevel = playerPtr->getLevel();

        print("Вы получили опыт за прохождение подземелья!", textSpeed, cyan);
        print("Уровень повышен: " + to_string(currentLevel) + " → " + to_string(newLevel), textSpeed, green);

        int hpBonus = 10;
        int manaBonus = 5;
        playerPtr->setMaxHP(playerPtr->getMaxHP() + hpBonus);
        playerPtr->setCurrentHP(playerPtr->getCurrentHP() + hpBonus);
        playerPtr->setMaxMana(playerPtr->getMaxMana() + manaBonus);
        playerPtr->setCurrentMana(playerPtr->getCurrentMana() + manaBonus);

        print("Бонусы: +" + to_string(hpBonus) + " HP, +" + to_string(manaBonus) + " маны", textSpeed, magenta);
        print("Новые характеристики:", textSpeed, cyan);
        print("HP: " + to_string(playerPtr->getCurrentHP()) + "/" + to_string(playerPtr->getMaxHP()), textSpeed, yellow);
        print("Мана: " + to_string(playerPtr->getCurrentMana()) + "/" + to_string(playerPtr->getMaxMana()), textSpeed, cyan);
    }

    print("Всего золота: " + to_string(playerPtr->getGold()), textSpeed, cyan);
    print("Возвращаемся в меню локаций...", textSpeed, none);
    wait(3);

    if (locationMenuPtr) {
        locationMenuPtr->show();
    }
}
