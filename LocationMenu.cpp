#include "LocationMenu.h"
#include "City.h"
#include "Dungeon.h" 
#include "MainMenu.h"
#include "Player.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace utils;
using namespace utils::color;

LocationMenu::LocationMenu(City* city) : cityPtr(city), dungeonPtr(nullptr), mainMenuPtr(nullptr) {}

void LocationMenu::setDungeon(Dungeon* dungeon) {
    dungeonPtr = dungeon;
}

void LocationMenu::setMainMenu(MainMenu* menu) {
    mainMenuPtr = menu;
}

void LocationMenu::setPlayerForDungeon(Player* player) {
    if (dungeonPtr) {
        dungeonPtr->setPlayer(player);
    }
    if (cityPtr) {
        cityPtr->setPlayer(player);
    }
}

void LocationMenu::show() {
    system("cls");
    int choice;

    do {
        system("cls"); // Важно очищать экран внутри цикла
        cout << magenta << "+============================================================+" << none << endl;
        cout << magenta << "|" << yellow << "               *** ВЫБОР ЛОКАЦИИ ***                        " << magenta << "|" << none << endl;
        cout << magenta << "+============================================================+" << none << endl;
        cout << endl;

        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "|" << yellow << "                Куда вы хотите пойти?                     " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << green << "[1]" << cyan << " Город" << string(47, ' ') << "|" << none << endl;
        cout << cyan << "|" << gray << "     Торговцы, квесты, отдых...                           " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << yellow << "[2]" << cyan << " Пещера" << string(46, ' ') << "|" << none << endl;
        cout << cyan << "|" << gray << "     Опасные монстры и сокровища...                       " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        // Кнопка появляется только после разговора
        if (City::hasMinerUnlockedBoss()) {
            cout << cyan << "| " << red << "[3]" << cyan << " Заброшенная шахта (БОСС)" << string(29, ' ') << "|" << none << endl;
            cout << cyan << "|" << gray << "     Сразитесь с Каменным Пожирателем                     " << cyan << "|" << none << endl;
            cout << cyan << "+----------------------------------------------------------+" << none << endl;
        }

        cout << cyan << "| " << red << "[0]" << cyan << " Главное меню" << string(40, ' ') << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        cout << blue << "Ваш выбор: " << none;
        choice = rightValue();

        switch (choice) {
        case 1:
            if (cityPtr) {
                print("Вы направляетесь в город...", textSpeed, green);
                wait(1);
                cityPtr->enter();
            }
            else {
                print("Город недоступен!", textSpeed, red);
                wait(1);
            }
            break;

        case 2:
            if (dungeonPtr) {
                print("Вы спускаетесь в пещеру...", textSpeed, yellow);
                wait(1);
                dungeonPtr->enter();
            }
            else {
                print("Пещера недоступна!", textSpeed, red);
                wait(1);
            }
            break;

        case 3: // Вход в босс-локацию
            if (City::hasMinerUnlockedBoss()) {
                if (dungeonPtr) {
                    print("Вы идете в Заброшенную шахту...", textSpeed, red);
                    print("Здесь пахнет опасностью...", textSpeed, gray);
                    wait(2);
                    dungeonPtr->enter(); // Запускаем обычный данж (пока без босса)
                }
            }
            else {
                print("Нет такого варианта", textSpeed, red);
                wait(1);
            }
            break;

        case 0:
            print("Возврат в главное меню...", textSpeed, cyan);
            wait(1);
            if (mainMenuPtr) {
                mainMenuPtr->show();
            }
            return;

        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }
    } while (choice != 0);
}
