#include "MainMenu.h"
#include "LocationMenu.h"

#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;
using namespace utils;
using namespace utils::color;


MainMenu::MainMenu(LocationMenu* locMenu) : locationMenuPtr(locMenu) {}

void MainMenu::showSettings() {
    system("cls");
    int choice;

    print("=== НАСТРОЙКИ ===", 1, none);
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
                    print("Некорректный ввод. Введите число от 0 до " + to_string(TextSpeeds::MAX_MANUAL) + ": ", 10, red);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else {
                    textSpeed = customSpeed;
                    print("Установлена скорость: " + to_string(textSpeed) + " мс", textSpeed, green);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }
            break;
        }
        case 0:
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            break;
        }
    } while (choice != 0);
}

void MainMenu::showAchievements() {
    int choice;

    do {
        system("cls");
        print("=== ДОСТИЖЕНИЯ ===", 1, none);
        print("\n0 - Вернуться в меню", 1, red);
        print("Выберите вариант: ", 1, blue);

        choice = rightValue();

        switch (choice) {
        case 0:
            print("Возврат в меню...", textSpeed, none);
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }
    } while (choice != 0);
}

void MainMenu::show() {
    int choice;
    int choicePlayer;
    bool playerCreated = false;
    Player player1;

    do {
        system("cls");
        print("Добро пожаловать в игру NNNNNN", textSpeed, none);

        if (playerCreated == false) {
            print("Начать игру (1)", textSpeed, green);
        }
        else if (playerCreated == true) {
            print("Продолжить игру (1)", textSpeed, green);
        }
        else {
            cout << "Ошибка";
        }

        print("Настройки (2)", textSpeed, none);
        print("Достижения (3)", textSpeed, none);
        print("Выйти из игры (0)", textSpeed, red);

        choice = rightValue();

        switch (choice) {
        case 1: {
            if (!playerCreated) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (!playerCreated) {
                    system("cls");

                    cout << "=== Создание персонажа ===" << endl;
                    cout << "1. Ручной ввод данных" << endl;
                    cout << "2. Случайная генерация" << endl;
                    cout << "Выберите вариант (1 или 2): " << endl;
                    choicePlayer = rightValue();

                    switch (choicePlayer) {
                    case 1: {
                        player1 = Player::createManual();
                        playerCreated = true;
                        break;
                    }

                    case 2: {
                        player1 = Player::generateRandom();
                        playerCreated = true;
                        break;
                    }

                    default: {
                        print("Нет такого варианта ответа", textSpeed, red);
                        wait(1);
                        break;
                    }
                    }
                }
            }

            if (locationMenuPtr) {
                locationMenuPtr->show();
            }
            else {
                cout << "Ошибка: меню локаций недоступно" << endl;
                wait(2);
            }
            break;
        }

        case 2:
            showSettings();
            break;

        case 3:
            showAchievements();
            break;

        case 0:
            print("Спасибо за игру! До свидания!", 30, green);
            wait(1);
            return;

        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }

    } while (choice != 0);
}

