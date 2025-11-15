#include "City.h"
#include "LocationMenu.h"

#include "utils.h"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace utils;
using namespace utils::color;

City::City() : locationMenuPtr(nullptr) {}

void City::setLocationMenu(LocationMenu* locMenu) {
    locationMenuPtr = locMenu;
}

string City::getDescription() const {
    return "Вы находитесь в оживленном средневековом городе. ";
}

void City::visitHome() {
    system("cls");
    int choice;

    print("Вы зашли к себе домой", textSpeed, none);
    print("Вы видите там", textSpeed, none);
    print("Кровать (1) \nОкно (2) \nКнигу (3) \nВыйти из дома (0) ", textSpeed, yellow);
    print("Что вы хотите сделать ", textSpeed, blue);

    do {
        choice = rightValue();

        switch (choice) {
        case 1:
            print("Вы легли на кровать и уснули", textSpeed, none);
            break;
        case 2:
            print("Вы посмотрели в окно и увидели оживленный город", textSpeed, none);
            break;
        case 3:
            print("Вы взяли книгу в руки открыли и немного почитали её", textSpeed, green);
            break;
        case 0:
            print("Вы вышли из дома", textSpeed, none);
            wait(1);
            enter(); // Возвращаемся к выбору зданий
            return;
        default:
            print("Вы ничего не сделали", textSpeed, red);
            break;
        }
    } while (choice != 0);
}

void City::visitLibrary() {
    system("cls");
    int choice;

    print("Вы зашли в тихую библиотеку", textSpeed, none);
    print("Вы видите там", textSpeed, none);
    print("Стеллажи с книгами (1) \nЧитальный зал (2) \nБиблиотекаря (3) \nВыйти из библиотеки (0) ", textSpeed, yellow);
    print("Что вы хотите сделать ", textSpeed, blue);

    do {
        choice = rightValue();

        switch (choice) {
        case 1:
            print("Вы просмотрели старинные книги на полках", textSpeed, green);
            break;
        case 2:
            print("Вы устроились в читальном зале и углубились в изучение фолиантов", textSpeed, none);
            break;
        case 3:
            print("Вы спросили у библиотекаря о редких изданиях", textSpeed, none);
            break;
        case 0:
            print("Вы вышли из библиотеки", textSpeed, none);
            wait(1);
            enter(); // Возвращаемся к выбору зданий
            return;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            break;
        }
    } while (choice != 0);
}

void City::visitTavern() {
    system("cls");
    int choice;

    print("Вы зашли в шумную таверну", textSpeed, none);
    print("Вы видите там", textSpeed, none);
    print("Барную стойку (1)\nПоговорить с барменом (2) \nИгровой стол (3) \nМузыкантов (4)\nИгра в кости (5) \nВыйти из таверны (0) ", textSpeed, yellow);
    print("Что вы хотите сделать ", textSpeed, blue);

    do {
        choice = rightValue();

        switch (choice) {
        case 1:
            print("Вы подошли к барной стойке и заказали эль", textSpeed, green);
            break;
        case 2: {
            int chance = rand() % 100;
            if (chance < 15) {
                print("У меня для тебя кое что есть ", textSpeed, magenta);
            }
            else {
                print("Вы хорошо поговорили с барменом на разные темы ", textSpeed, none);
            }
            break;
        }
        case 3:
            print("Вы сидели и поиграли с местными жителями", textSpeed, none);
            break;
        case 4:
            print("Вы послушали веселую музыку местных музыкантов", textSpeed, none);
            break;
        case 5:
            if (diceGame()) {
                print("Вы весело провели время и выиграли немного денег!", textSpeed, green);
            }
            else {
                print("Вы проиграли, но хорошо провели время!", textSpeed, yellow);
            }
            break;
        case 0:
            print("Вы вышли из таверны", textSpeed, none);
            wait(1);
            enter(); // Возвращаемся к выбору зданий
            return;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            break;
        }
    } while (choice != 0);
}

bool City::diceGame() {
    print("Игра в кости! Бросок...", 20, yellow);
    wait(1);

    int playerRoll = random(1, 6);
    int opponentRoll = random(1, 6);

    print("Вы выбросили: " + to_string(playerRoll), 20, blue);
    print("Оппонент выбросил: " + to_string(opponentRoll), 20, blue);

    if (playerRoll > opponentRoll) {
        print("Вы выиграли!", 20, green);
        return true;
    }
    else if (playerRoll < opponentRoll) {
        print("Вы проиграли!", 20, red);
        return false;
    }
    else {
        print("Ничья!", 20, yellow);
        return false;
    }
}

void City::enter() {
    system("cls");
    int choice;

    print(getDescription(), textSpeed, none);
    print("\nВ городе есть такие места как:", textSpeed, none);
    print("Библиотека (1) \nВаш дом (2) \nТаверна (3) \nУйти из города (0) ", textSpeed, yellow);
    print("Введите цифру места что бы туда пойти ", textSpeed, blue);

    do {
        choice = rightValue();

        switch (choice) {
        case 1:
            wait(1);
            visitLibrary();
            return; // Выходим из enter() после возврата из библиотеки
        case 2:
            visitHome();
            return; // Выходим из enter() после возврата из дома
        case 3:
            wait(1);
            visitTavern();
            return; // Выходим из enter() после возврата из таверны
        case 0:
            print("Вы ушли из города", textSpeed, none);
            wait(1);
            if (locationMenuPtr) {
                locationMenuPtr->show(); // Возврат к меню выбора локаций
            }
            return;
        case 666:
            print("тебе пока что нельзя сюда ", textSpeed, gray);
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            break;
        }
    } while (choice != 0);
}
