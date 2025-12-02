#include "MainMenu.h"
#include "LocationMenu.h"
#include "Player.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;
using namespace utils;
using namespace utils::color;

MainMenu::MainMenu(LocationMenu* locMenu) : locationMenuPtr(locMenu), currentPlayer(nullptr) {}

// Компактный и читаемый вывод истории
void MainMenu::showStoryIntro(const string& playerName) {
    system("cls");

    cout << endl;
    cout << yellow << "                       *** ПРЕДЫСТОРИЯ ***" << none << endl;
    cout << endl;

    // Блок 1
    print("Трое путешественников — " + playerName + " и его верные друзья Валера и Рома —", textSpeed, gray);
    print("возвращались из опасной экспедиции, неся с собой ценные древние реликвии.", textSpeed, gray);
    cout << endl;
    print("Последний привал вы устроили в знакомом лесу, строя планы на будущее", textSpeed, gray);
    print("и делясь мечтами.", textSpeed, gray);
    cout << endl << endl;

    print("Никто из вас не подозревал, что это станет вашим последним вечером вместе...", textSpeed, red);
    wait(4);

    system("cls");
    cout << endl;
    cout << yellow << "                        *** НАПАДЕНИЕ ***" << none << endl;
    cout << endl;

    // Блок 2
    print("На рассвете на лагерь напала банда головорезов.", textSpeed, red);
    cout << endl;
    print("В завязавшейся кровавой схватке Валера и Рома погибли,", textSpeed, red);
    print("прикрывая отступление, которое начал " + playerName + ".", textSpeed, red);
    cout << endl << endl;

    print("Чудом выжив, вы потеряли не только друзей, но и все добытые артефакты,", textSpeed, yellow);
    print("которые забрали нападавшие.", textSpeed, yellow);
    wait(4);

    system("cls");
    cout << endl;
    cout << yellow << "                      *** НОВАЯ НАДЕЖДА ***" << none << endl;
    cout << endl;

    // Блок 3
    print("Истекая кровью и подавленный горем, " + playerName + " с трудом добрался", textSpeed, cyan);
    print("до опушки леса.", textSpeed, cyan);
    cout << endl;
    print("Вдали мерцали огни города — последняя надежда на спасение", textSpeed, cyan);
    print("и возможность начать всё сначала...", textSpeed, green);
    cout << endl << endl;

    print("Нажмите Enter, чтобы отправиться в город...", textSpeed, gray);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void MainMenu::showSettings() {
    system("cls");
    int choice;

    cout << cyan << "+----------------------------------------------------------+" << none << endl;
    cout << cyan << "|" << yellow << "                    *** НАСТРОЙКИ ***                     " << cyan << "|" << none << endl;
    cout << cyan << "+----------------------------------------------------------+" << none << endl;
    cout << cyan << "|" << green << " Текущая скорость: " << yellow << textSpeed << " мс/символ"
        << string(26 - to_string(textSpeed).length(), ' ') << cyan << "|" << none << endl;
    cout << cyan << "+----------------------------------------------------------+" << none << endl;
    cout << cyan << "| " << green << "[1]" << cyan << " Медленная скорость (" << yellow << TextSpeeds::SLOW
        << " мс)" << string(22 - to_string(TextSpeeds::SLOW).length(), ' ') << cyan << "|" << none << endl;
    cout << cyan << "| " << green << "[2]" << cyan << " Средняя скорость (" << yellow << TextSpeeds::MEDIUM
        << " мс)" << string(24 - to_string(TextSpeeds::MEDIUM).length(), ' ') << cyan << "|" << none << endl;
    cout << cyan << "| " << green << "[3]" << cyan << " Быстрая скорость (" << yellow << TextSpeeds::FAST
        << " мс)" << string(24 - to_string(TextSpeeds::FAST).length(), ' ') << cyan << "|" << none << endl;
    cout << cyan << "| " << green << "[4]" << cyan << " Мгновенный текст (" << yellow << TextSpeeds::INSTANT
        << " мс)" << string(24 - to_string(TextSpeeds::INSTANT).length(), ' ') << cyan << "|" << none << endl;
    cout << cyan << "| " << green << "[5]" << cyan << " Настроить вручную" << string(32, ' ') << cyan << "|" << none << endl;
    cout << cyan << "+----------------------------------------------------------+" << none << endl;
    cout << cyan << "| " << red << "[0]" << cyan << " Вернуться в главное меню"
        << string(29, ' ') << cyan << "|" << none << endl;
    cout << cyan << "+----------------------------------------------------------+" << none << endl;

    do {
        cout << blue << "Выберите вариант: " << none;
        choice = rightValue();

        switch (choice) {
        case 1:
            textSpeed = TextSpeeds::SLOW;
            print("Установлена медленная скорость текста", textSpeed, green);
            wait(1);
            break;
        case 2:
            textSpeed = TextSpeeds::MEDIUM;
            print("Установлена средняя скорость текста", textSpeed, green);
            wait(1);
            break;
        case 3:
            textSpeed = TextSpeeds::FAST;
            print("Установлена быстрая скорость текста", textSpeed, green);
            wait(1);
            break;
        case 4:
            textSpeed = TextSpeeds::INSTANT;
            print("Установлен мгновенный вывод текста", textSpeed, green);
            wait(1);
            break;
        case 5: {
            print("Введите скорость (0-" + to_string(TextSpeeds::MAX_MANUAL) + " мс): ", textSpeed, blue);
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
                    wait(1);
                    break;
                }
            }
            break;
        }
        case 0:
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }
    } while (choice != 0);
}



int MainMenu::show() {
    int choice;
    int choicePlayer;
    static bool playerCreated = false;
    static Player player1;

    do {
        system("cls");

        cout << magenta << "+============================================================+" << none << endl;
        cout << magenta << "|" << yellow << "                                                            " << magenta << "|" << none << endl;
        cout << magenta << "|" << yellow << "          *** Добро пожаловать в игру NNNNNN ***           " << magenta << "|" << none << endl;
        cout << magenta << "|" << yellow << "                                                            " << magenta << "|" << none << endl;
        cout << magenta << "+============================================================+" << none << endl;
        cout << endl;

        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        if (!playerCreated) {
            cout << cyan << "| " << green << "[1]" << cyan << " Начать игру (Создать персонажа)"
                << string(23, ' ') << cyan << "|" << none << endl;
        }
        else {
            string playerInfo = "Продолжить игру (" + player1.getName() + ")";
            int spaces = 54 - playerInfo.length();
            if (spaces < 0) spaces = 0;

            cout << cyan << "| " << green << "[1]" << cyan << " " << playerInfo
                << string(spaces, ' ') << "|" << none << endl;
        }

        cout << cyan << "| " << yellow << "[2]" << cyan << " Настройки"
            << string(45, ' ') << cyan << "|" << none << endl;

        if (playerCreated) {
            string profileText = "Профиль (" + player1.getName() + ")";
            int spaces = 54 - profileText.length() - 1;
            if (spaces < 0) spaces = 0;

            cout << cyan << "| " << magenta << "[3]" << cyan << " " << profileText
                << string(spaces, ' ') << "|" << none << endl;
        }

        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << red << "[0]" << cyan << " Выйти из игры"
            << string(41, ' ') << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        cout << blue << "Ваш выбор: " << none;
        choice = rightValue();

        switch (choice) {
        case 1: {
            if (!playerCreated) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (!playerCreated) {
                    system("cls");

                    cout << cyan << "+----------------------------------------------------------+" << none << endl;
                    cout << cyan << "|" << yellow << "              *** СОЗДАНИЕ ПЕРСОНАЖА ***                  " << cyan << "|" << none << endl;
                    cout << cyan << "+----------------------------------------------------------+" << none << endl;
                    cout << cyan << "| " << green << "[1]" << cyan << " Ручной ввод данных"
                        << string(36, ' ') << cyan << "|" << none << endl;
                    cout << cyan << "| " << green << "[2]" << cyan << " Случайная генерация"
                        << string(35, ' ') << cyan << "|" << none << endl;
                    cout << cyan << "+----------------------------------------------------------+" << none << endl;

                    cout << blue << "Выберите вариант (1 или 2): " << none;
                    choicePlayer = rightValue();

                    switch (choicePlayer) {
                    case 1: {
                        player1 = Player::createManual();
                        if (player1.getName() != "") {
                            playerCreated = true;
                            currentPlayer = &player1;
                        }
                        else {
                            print("Возврат к выбору...", textSpeed, cyan);
                            wait(1);
                        }
                        break;
                    }

                    case 2: {
                        player1 = Player::generateRandom();
                        playerCreated = true;
                        currentPlayer = &player1;
                        break;
                    }

                    default: {
                        print("Нет такого варианта ответа", textSpeed, red);
                        wait(1);
                        break;
                    }
                    }

                    // Если персонаж создан - предлагаем историю
                    if (playerCreated) {
                        if (locationMenuPtr) {
                            locationMenuPtr->setPlayerForDungeon(&player1);
                        }

                        system("cls");
                        cout << cyan << "+----------------------------------------------------------+" << none << endl;
                        cout << cyan << "| " << yellow << "Персонаж " << player1.getName() << " успешно создан!" << string(37 - player1.getName().length(), ' ') << "|" << none << endl;
                        cout << cyan << "+----------------------------------------------------------+" << none << endl;
                        cout << endl;
                        
                        print("Хотите узнать предысторию вашего героя?", textSpeed, yellow);
                        cout << endl;
                        cout << green << "[1]" << cyan << " Да, рассказать историю" << none << endl;
                        cout << green << "[2]" << cyan << " Нет, перейти к выбору локации" << none << endl;
                        cout << endl;
                        cout << blue << "Ваш выбор: " << none;

                        int storyChoice = rightValue();
                        if (storyChoice == 1) {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            showStoryIntro(player1.getName());
                        }
                        else {
                            print("Вы пропускаете вступление...", textSpeed, gray);
                            wait(1);
                        }
                    }
                }
            }

            if (locationMenuPtr) {
                locationMenuPtr->show();
            }
            else {
                print("Ошибка: меню локаций недоступно", textSpeed, red);
                wait(2);
            }
            break;
        }

        case 2:
            showSettings();
            break;

        case 3:
            if (playerCreated) {
                
                playerPtr->showProfile(currentPlayer);
               
            }
            else {
                print("Сначала создайте персонажа!", textSpeed, red);
                wait(1);
            }
            break;

        case 0:
            system("cls");
            cout << magenta << "+----------------------------------------------------------+" << none << endl;
            cout << magenta << "|" << green << "          Спасибо за игру! До свидания!                   " << magenta << "|" << none << endl;
            cout << magenta << "+----------------------------------------------------------+" << none << endl;
            wait(2);
            return 0;

        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }

    } while (choice != 0);
    return 0;
}
