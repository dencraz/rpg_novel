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
                   int turnSpent;
                case 'e':
                case 'E':
                    turnSpent = playerPtr->openInventoryMenu(); // Открывает меню и возвращает true, если выпили зелье
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
// ... (предыдущий код) ...

void Dungeon::enterBossBattle() {
    if (!playerPtr) {
        cout << red << "Ошибка: игрок не найден!" << none << endl;
        return;
    }

    system("cls");
    // Атмосферное вступление
    cout << red << "+==========================================================+" << none << endl;
    cout << red << "| " << yellow << "            ЗАБРОШЕННАЯ ШАХТА - ЛОГОВО БОССА            " << red << "|" << none << endl;
    cout << red << "+==========================================================+" << none << endl;
    cout << endl;

    print("Вы входите в огромный подземный зал...", textSpeed, gray);
    print("Земля дрожит под ногами.", textSpeed, red);
    print("Из темноты появляются два горящих красных глаза.", textSpeed, bright_red);
    wait(2);
    print("\nКАМЕННЫЙ ПОЖИРАТЕЛЬ: 'КТО ПОСМЕЛ НАРУШИТЬ МОЙ СОН?'", textSpeed, yellow);
    wait(2);

    // Создаем босса: 600 HP, урон 20-40
    Monster boss(600, "Каменный Пожиратель", 20, 40, "Гигантская тварь из живого камня", true);

    bool inBattle = true;
    int turnCounter = 0;

    while (inBattle && playerPtr->isAlive() && boss.isAlive()) {
        turnCounter++;
        system("cls");

        // ИНТЕРФЕЙС ИГРОКА
        cout << green << "+----------------------------------------------------------+" << none << endl;
        cout << green << "| ИГРОК: " << yellow << playerPtr->getName() << green;
        cout << string(42 - playerPtr->getName().length(), ' ') << "|" << none << endl;
        cout << green << "| HP: " << yellow << playerPtr->getCurrentHP() << "/" << playerPtr->getMaxHP()
            << green << " | Мана: " << cyan << playerPtr->getCurrentMana() << "/" << playerPtr->getMaxMana()
            << green << " | Золото: " << yellow << playerPtr->getGold() << green << "              |" << none << endl;
        cout << green << "+----------------------------------------------------------+" << none << endl;
        cout << endl;

        // ИНТЕРФЕЙС БОССА
        cout << red << "=== БОСС: " << boss.getName() << " ===" << none << endl;

        // Рисуем полоску здоровья босса
        int hpPercent = (boss.getCurrentHP() * 40) / boss.getMaxHP();
        cout << "HP: " << red << "[";
        for (int i = 0; i < 40; ++i) {
            if (i < hpPercent) cout << "#";
            else cout << " ";
        }
        cout << "] " << boss.getCurrentHP() << "/" << boss.getMaxHP() << none << endl;
        cout << gray << "Описание: " << boss.getDescription() << none << endl;
        cout << endl;

        // НОВОЕ МЕНЮ ДЕЙСТВИЙ (W, R, E, Q)
        cout << cyan << "+------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << yellow << "[w] Атака" << cyan << "               "
            << yellow << "[r] Мощный удар (30 маны)" << cyan << " |" << none << endl;
        cout << cyan << "| " << yellow << "[e] Инвентарь" << cyan << "           "
            << yellow << "[q] Побег" << cyan << "                 |" << none << endl;
        cout << cyan << "+------------------------------------------------------+" << none << endl;
        cout << "Ваш выбор: ";

        char key;
        cin >> key;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера

        bool turnSpent = false;

        switch (key) {
        case 'w':
        case 'W': { // Обычная атака
            int dmg = utils::random(25, 35) + (playerPtr->getLevel() * 2);
            boss.takeDamage(dmg);
            print("Вы атакуете Пожирателя! Урон: " + to_string(dmg), textSpeed, green);
            turnSpent = true;
            break;
        }
        case 'r':
        case 'R': { // Мощный удар
            if (playerPtr->getCurrentMana() >= 30) {
                playerPtr->useMana(30);
                int dmg = utils::random(50, 70) + (playerPtr->getLevel() * 3);
                boss.takeDamage(dmg);
                print("СОКРУШИТЕЛЬНЫЙ УДАР! Урон: " + to_string(dmg), textSpeed, cyan);
                turnSpent = true;
            }
            else {
                print("Недостаточно маны!", textSpeed, red);
                wait(1);
                turnSpent = false;
            }
            break;
        }
        case 'e':
        case 'E':
        {
            const auto& inventory = playerPtr->getInventory();

            if (inventory.empty()) {
                print("Инвентарь пуст!", textSpeed, red);
                wait(2);
                turnSpent = false; // Ход не тратится
                break;
            }

            int selectedIndex = 0;
            bool inInventory = true;
            bool itemUsed = false;

            while (inInventory) {
                system("cls");

                // Рисуем статус игрока (чтобы не терять контекст)
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

                    // Выравнивание
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
                    // Ничего не делаем или пишем ошибку
                    break;
                }
            }

            // Если использовали предмет, то ход потрачен. Если просто открыли и закрыли — нет.
            turnSpent = itemUsed;
            system("cls"); // Очищаем экран перед отрисовкой боя
        }
        break;

        case 'q':
        case 'Q': { // Побег
            if (utils::random(1, 100) <= 5) { // Шанс сбежать от босса очень мал (5%)
                print("Вам чудом удалось улизнуть!", textSpeed, green);
                inBattle = false;
                wait(2);
                return;
            }
            else {
                print("Пожиратель перекрывает выход! Бежать некуда!", textSpeed, red);
                turnSpent = true; // Попытка побега тратит ход
            }
            break;
        }
        default:
            print("Используйте W, R, E или Q!", textSpeed, red);
            wait(1);
            break;
        }

        if (!turnSpent) continue;

        // Проверка победы
        if (!boss.isAlive()) {
            inBattle = false;
            break;
        }

        wait(1);
        cout << endl;

        // ХОД БОССА (AI)
        if (turnCounter % 4 == 0) {
            // Спец-атака: Камнепад
            print("Пожиратель вызывает КАМНЕПАД!", textSpeed, magenta);
            int dmg = utils::random(40, 60);
            playerPtr->takeDamage(dmg);
            print("Вас завалило камнями! Урон: " + to_string(dmg), textSpeed, red);
        }
        else if (boss.getCurrentHP() < 200 && utils::random(1, 100) <= 30) {
            // Лечение
            print("Пожиратель восстанавливает каменную броню...", textSpeed, yellow);
            boss.heal(50);
            print("Босс восстановил 50 HP!", textSpeed, green);
        }
        else {
            // Обычная атака
            int dmg = boss.getDamage();
            playerPtr->takeDamage(dmg);
            print("Пожиратель бьет вас! Урон: " + to_string(dmg), textSpeed, red);
        }

        if (!playerPtr->isAlive()) {
            print("В глазах темнеет...", textSpeed, red);
            wait(2);
            break;
        }
        wait(2);
    }

    // ИТОГИ
    system("cls");
    if (playerPtr->isAlive()) {
        cout << yellow << R"(
             _    _  _____  _____  _____  _____  _____  __   __
            | |  | ||_   _||  __ \|_   _||  _  ||  _  | \ \ / /
            | |  | |  | |  | |  \/  | |  | | | || | | |  \ V / 
            | |/\| |  | |  | | __   | |  | | | || | | |   \ /  
            \  /\  / _| |_ | |_\ \  | |  \ \_/ /\ \_/ /   | |  
             \/  \/  \___/  \____/  \_/   \___/  \___/    \_/  
        )" << none << endl;
        print("ПОБЕДА! Каменный Пожиратель повержен!", textSpeed, green);
        print("Вы получаете 2000 золота и вечную славу!", textSpeed, yellow);
        playerPtr->addGold(2000);
        wait(3);
    }
    else {
        cout << red << R"(
              _____   ___  ___  ___  _____   _____  _   _  _____  ______ 
             |  __ \ / _ \ |  \/  | |  ___| |  _  || | | ||  ___| | ___ \
             | |  \// /_\ \| .  . | | |__   | | | || | | || |__   | |_/ /
             | | __ |  _  || |\/| | |  __|  | | | || | | ||  __|  |    / 
             | |_\ \| | | || |  | | | |___  \ \_/ /\ \_/ /| |___  | |\ \ 
              \____/\_| |_/\_|  |_/ \____/   \___/  \___/ \____/  \_| \_|
        )" << none << endl;
        print("Вы погиб в бою с древним злом...", textSpeed, red);
        playerPtr->setCurrentHP(playerPtr->getMaxHP()); // Воскрешение
        playerPtr->setGold(playerPtr->getGold() / 2);   // Штраф
        wait(3);
    }

    if (locationMenuPtr) locationMenuPtr->show();
}


