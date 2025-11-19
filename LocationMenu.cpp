#include "LocationMenu.h"
#include "City.h"
#include "MainMenu.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace utils;
using namespace utils::color;

LocationMenu::LocationMenu(City* city) : cityPtr(city), mainMenuPtr(nullptr) {}

void LocationMenu::setMainMenu(MainMenu* menu) {
    mainMenuPtr = menu;
}

void LocationMenu::show() {
    system("cls");
    int choice;

    print("Куда вы хотите пойти", textSpeed, none);
    print("Город (1)\nПещера (2)\nГлавное меню (0)", textSpeed, yellow);

    do {
        choice = rightValue();

        switch (choice) {
        case 1:
            if (cityPtr) {
                cityPtr->enter();
                return; 
            }
            break;
        case 2:
            print("Пещера пока не реализована", textSpeed, magenta);
            break;
        case 0:
            print("Возврат в главное меню...", textSpeed, none);
            wait(1);
            if (mainMenuPtr) {
                mainMenuPtr->show(); 
            }
            return;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            break;
        }
    } while (choice != 0);
}
