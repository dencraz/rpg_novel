#include <iostream>
#include <thread>
#include <chrono>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <random>

#include "function.h"
#include "utils.h"
using namespace std;
using namespace utils;
using namespace utils::color;


void settingsMenu() {
    system("cls");
    int choice;

    print("=== НАСТРОЙКИ ===", 1, cyan);
    print("Текущая скорость текста: " + to_string(textSpeed) + " мс/символ", textSpeed, yellow);
    print("1 - Медленная скорость (" + to_string(TextSpeeds::SLOW) + " мс)", 1, green);
    print("2 - Средняя скорость (" + to_string(TextSpeeds::MEDIUM) + " мс)", 1, yellow);
    print("3 - Быстрая скорость (" + to_string(TextSpeeds::FAST) + " мс)", 1, green);
    print("4 - Мгновенный текст (" + to_string(TextSpeeds::INSTANT) + " мс)", 1, yellow);
    print("5 - Настроить вручную (0-" + to_string(TextSpeeds::MAX_MANUAL) + " мс)", 1, green);
    print("0 - Вернуться в главное меню", 1, red);

    do {
        print("Выберите вариант: ", 1, blue);

        choice = rightValue();

        switch (choice) {
        case 1:
            textSpeed = TextSpeeds::SLOW;
            print("Установлена медленная скорость текста", textSpeed, green);
            break;
        case 2:
            textSpeed = TextSpeeds::MEDIUM;
            print("Установлена средняя скорость текста", textSpeed, green);
            break;
        case 3:
            textSpeed = TextSpeeds::FAST;
            print("Установлена быстрая скорость текста", textSpeed, green);
            break;
        case 4:
            textSpeed = TextSpeeds::INSTANT;
            print("Установлен мгновенный вывод текста", textSpeed, green);
            break;
        case 5: {
            print("Введите скорость текста в миллисекундах (0-" + to_string(TextSpeeds::MAX_MANUAL) + "): ", textSpeed, blue);
            int customSpeed;
            while (true) {
                cin >> customSpeed;
                if (cin.fail() || customSpeed < 0 || customSpeed > TextSpeeds::MAX_MANUAL) {
                    print("Некорректный ввод. Введите число от 0 до " + to_string(TextSpeeds::MAX_MANUAL) + ": ", 10, bright_red);
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else {
                    textSpeed = customSpeed;
                    print("Установлена скорость: " + to_string(textSpeed) + " мс", textSpeed, green);
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
            }
        } break;
        case 0:
            startMenu();
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, bright_red);
            break;
        }
    } while (choice != 0);
}

bool diceGame() {
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
        print("Вы проиграли!", 20, bright_red);
        return false;
    }
    else {
        print("Ничья!", 20, yellow);
        return false;
    }
}



void acthome() {
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
            print("Вы легли на кровать и уснули", textSpeed, magenta);
            break;
        case 2:
            print("Вы посмотрели в окно и увидели оживленный город", textSpeed, cyan);
            break;
        case 3:
            print("Вы взяли книгу в руки открыли и немного почитали её", textSpeed, green);
            break;
        case 0:
            print("Вы вышли из дома", textSpeed, blue);
            city();
            break;
        default:
            print("Вы ничего не сделали", textSpeed, bright_red);
            break;
        }
    } while (choice != 0);
    wait(1);
    system("cls");
}

void actLibrary() {
    system("cls");
    int choice;


    print("Вы зашли в тихую библиотеку", textSpeed, cyan);
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
            print("Вы устроились в читальном зале и углубились в изучение фолиантов", textSpeed, magenta);
            break;
        case 3:
            print("Вы спросили у библиотекаря о редких изданиях", textSpeed, cyan);
            break;
        case 0:
            print("Вы вышли из библиотеки", textSpeed, blue);
            city();
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, bright_red);
            break;
        }
    } while (choice != 0);
    wait(1);
    system("cls");
}

void actTavern() {
    system("cls");

    int choice;
    int chance;

    print("Вы зашли в шумную таверну", textSpeed, cyan);
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
            chance = rand() % 100;
            if (chance < 15) {
                print("У меня для тебя кое что есть ", textSpeed, none);
            }
            else {
                print("Вы хорошо поговорили с барменом на разные темы ", textSpeed, none);
            }
            break;
        }
        case 3:
            print("Вы сидели и поиграли с местными жителями", textSpeed, cyan);
            break;
        case 4:
            print("Вы послушали веселую музыку местных музыкантов", textSpeed, cyan);
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
            print("Вы вышли из таверны", textSpeed, blue);
            city();
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, bright_red);
            break;
        }
    } while (choice != 0);

    wait(1);
    system("cls");
}

void menuLocation();

int city() {
    system("cls");
    int choice;

    print("В городе есть такие места как:", textSpeed, none);
    print("Библиотека (1) \nВаш дом (2) \nТаверна (3) \nУйти из города (0) ", textSpeed, yellow);
    print("Введите цифру места что бы туда пойти ", textSpeed, blue);
    do {
        choice = rightValue();

        switch (choice) {
        case 1:
            wait(1);
            actLibrary();
            break;
        case 2:
            acthome();
            break;
        case 3:
            wait(1);
            actTavern();
            break;
        case 0:
            print("Вы ушли из города", textSpeed, blue);
            menuLocation();
            break;
        case 666:
            hrprint("тебе пока что нельзя сюда ", 200, bright_red);
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, bright_red);
            break;
        }
    } while (choice != 0);

    return 0;
}

void menuLocation() {
    system("cls");
    int choice;
    print("Куда вы хотите пойти", textSpeed, none);
    print("Город (1)\nПещера (2)\nГлавное меню (0)", textSpeed, yellow);
    do {
        choice = rightValue();
        switch (choice) {
        case 1:
            city();
            break;
        case 2:
            break;
        case 0:
            startMenu();
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, bright_red);
            break;
        }
    } while (choice != 0);
    wait(1);
    ;
}

void achievements() {
    int choice;

    do {
        system("cls");
        print("=== ДОСТИЖЕНИЯ ===", 1, cyan);



        print("\n0 - Вернуться в меню", 1, red);
        print("Выберите вариант: ", 1, blue);

        choice = rightValue();

        switch (choice) {
        case 0:
            print("Возврат в меню...", textSpeed, blue);
            startMenu();
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, bright_red);
            wait(1);
            break;
        }
    } while (choice != 0);
}

int startMenu() {
    int choice;
    system("cls");
    print("Добро пожаловать в игру NNNNNN", textSpeed, none);
    print("Начать игру (1)", textSpeed, green);
    print("Настройки (2)", textSpeed, none);
    print("Достижения (3)", textSpeed, none);
    print("Выйти из игры (0)", textSpeed, red);
    do {
        choice = rightValue();

        switch (choice) {
        case 1:
            menuLocation();
            break;
        case 2:
            settingsMenu();
            break;
        case 3:
            achievements();
            break;
        case 0:
            print("Спасибо за игру! До свидания!", 30, green);
            wait(1);
            return 0;
        default:
            print("Нет такого варианта ответа", textSpeed, bright_red);
            break;
        }

        wait(1);
    } while (choice != 0);

    return 0;
}

