#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <random>
using namespace std;
bool Taverncheck = 0;
bool Librarycheck = 0;
bool homecheck = 0;

namespace color {
    const char* none = "\033[0m";
    const char* red = "\033[31m";
    const char* green = "\033[32m";
    const char* yellow = "\033[33m";
    const char* blue = "\033[34m";
    const char* magenta = "\033[35m";
    const char* cyan = "\033[36m";
    const char* white = "\033[37m";
    const char* bright_red = "\033[91m";
}

namespace TextSpeeds {
    const int SLOW = 40;
    const int MEDIUM = 20;
    const int FAST = 10;
    const int INSTANT = 0;
    const int MAX_MANUAL = 100;
}


int textSpeed = TextSpeeds::MEDIUM;

void wait(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

void print(const string& text, int time = -1, const char* text_color = color::none) {
    if (time == -1) time = textSpeed;

    for (char c : text) {
        cout << text_color << c << color::none << flush;
        this_thread::sleep_for(chrono::milliseconds(time));
    }
    cout << '\n';
}

void hrprint(const string& text, int time = -1, const char* text_color = color::red) {
    if (time == -1) time = textSpeed;

    for (char c : text) {
        cout << text_color << (char)std::toupper(c) << color::none << flush;
        this_thread::sleep_for(chrono::milliseconds(time));
    }
    cout << '\n';
}

int random(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

int rightValue() {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            print("Некорректный ввод. Пожалуйста, введите число.", 10, color::bright_red);

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}
int startMenu();
void settingsMenu() {
    system("cls");
    int choice;

    
    print("=== НАСТРОЙКИ ===", 1, color::cyan);
    print("Текущая скорость текста: " + to_string(textSpeed) + " мс/символ", -1, color::yellow);
    print("1 - Медленная скорость (" + to_string(TextSpeeds::SLOW) + " мс)", 1, color::green);
    print("2 - Средняя скорость (" + to_string(TextSpeeds::MEDIUM) + " мс)", 1, color::yellow);
    print("3 - Быстрая скорость (" + to_string(TextSpeeds::FAST) + " мс)", 1, color::green);
    print("4 - Мгновенный текст (" + to_string(TextSpeeds::INSTANT) + " мс)", 1, color::yellow);
    print("5 - Настроить вручную (0-" + to_string(TextSpeeds::MAX_MANUAL) + " мс)", 1, color::green);
    print("0 - Вернуться в главное меню", 1, color::red);

    do {
        print("Выберите вариант: ", 1, color::blue);

        choice = rightValue();

        switch (choice) {
        case 1:
            textSpeed = TextSpeeds::SLOW;
            print("Установлена медленная скорость текста", -1, color::green);
            break;
        case 2:
            textSpeed = TextSpeeds::MEDIUM;
            print("Установлена средняя скорость текста", -1, color::green);
            break;
        case 3:
            textSpeed = TextSpeeds::FAST;
            print("Установлена быстрая скорость текста", -1, color::green);
            break;
        case 4:
            textSpeed = TextSpeeds::INSTANT;
            print("Установлен мгновенный вывод текста", -1, color::green);
            break;
        case 5:
        {
            print("Введите скорость текста в миллисекундах (0-" + to_string(TextSpeeds::MAX_MANUAL) + "): ", -1, color::blue);
            int customSpeed;
            while (true) {
                cin >> customSpeed;
                if (cin.fail() || customSpeed < 0 || customSpeed > TextSpeeds::MAX_MANUAL) {
                    print("Некорректный ввод. Введите число от 0 до " + to_string(TextSpeeds::MAX_MANUAL) + ": ", 10, color::bright_red);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else {
                    textSpeed = customSpeed;
                    print("Установлена скорость: " + to_string(textSpeed) + " мс", -1, color::green);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }
        }
        break;
        case 0:
            startMenu();
            break;
        default:
            print("Нет такого варианта ответа", -1, color::bright_red);
            break;
        }

        

    } while (choice != 0);
}

bool diceGame() {
    print("Игра в кости! Бросок...", 20, color::yellow);
    wait(1);

    int playerRoll = random(1, 6);
    int opponentRoll = random(1, 6);

    print("Вы выбросили: " + to_string(playerRoll), 20, color::blue);
    print("Оппонент выбросил: " + to_string(opponentRoll), 20, color::blue);

    if (playerRoll > opponentRoll) {
        print("Вы выиграли!", 20, color::green);
        return true;
    }
    else if (playerRoll < opponentRoll) {
        print("Вы проиграли!", 20, color::bright_red);
        return false;
    }
    else {
        print("Ничья!", 20, color::yellow);
        return false;
    }
}

int city();

void acthome() {
    system("cls");
    int choice;
    homecheck = 1;


    print("Вы зашли к себе домой");
    print("Вы видите там");
    print("Кровать (1) \nОкно (2) \nКнигу (3) \nВыйти из дома (0) ", -1, color::yellow);


    print("Что вы хотите сделать ", -1, color::blue);
    do {
        choice = rightValue();

        switch (choice) {
        case 1:
            print("Вы легли на кровать и уснули", -1, color::magenta);

            break;
        case 2:
            print("Вы посмотрели в окно и увидели оживленный город", -1, color::cyan);

            break;
        case 3:
            print("Вы взяли книгу в руки открыли и немного почитали её", -1, color::green);

            break;
        case 0:
            print("Вы вышли из дома", -1, color::blue);
            city();
            break;
        default:
            print("Вы ничего не сделали", -1, color::bright_red);
            break;
        }
    } while (choice != 0);
    wait(0.5);
    system("cls");
}

void actLibrary() {
    system("cls");
    int choice;
    Librarycheck = 1;

    print("Вы зашли в тихую библиотеку", -1, color::cyan);
    print("Вы видите там");
    print("Стеллажи с книгами (1) \nЧитальный зал (2) \nБиблиотекаря (3) \nВыйти из библиотеки (0) ", -1, color::yellow);
    print("Что вы хотите сделать ", -1, color::blue);

    do {
        choice = rightValue();

        switch (choice) {
        case 1:
            print("Вы просмотрели старинные книги на полках", -1, color::green);

            break;
        case 2:
            print("Вы устроились в читальном зале и углубились в изучение фолиантов", -1, color::magenta);

            break;
        case 3:
            print("Вы спросили у библиотекаря о редких изданиях", -1, color::cyan);

            break;
        case 0:
            print("Вы вышли из библиотеки", -1, color::blue);
            city();
            break;
        default:
            print("Нет такого варианта ответа", -1, color::bright_red);
            break;
        }
    } while (choice != 0);
    wait(0.5);
    system("cls");
}

void actTavern() {
    system("cls");
    
    int choice;
    bool shouldContinue = true;
    int chance;
    Taverncheck = 1;
    print("Вы зашли в шумную таверну", -1, color::cyan);
    print("Вы видите там");

    print("Барную стойку (1)\nПоговорить с барменом (2) \nИгровой стол (3) \nМузыкантов (4)\nИгра в кости (5) \nВыйти из таверны (0) ", -1, color::yellow);


    print("Что вы хотите сделать ", -1, color::blue);
    do {
        choice = rightValue();

        switch (choice) {
        case 1:
            print("Вы подошли к барной стойке и заказали эль", -1, color::green);

            break;
        case 2:
        {
            chance = rand() % 100;

            if (chance < 15) {
                print("У меня для тебя кое что есть ");
            }
            else {
                print("Вы хорошо поговорили с барменом на разные темы ");
            }

            break;
        }
        case 3:
            print("Вы сидели и поиграли с местными жителями", -1, color::cyan);

            break;
        case 4:
            print("Вы послушали веселую музыку местных музыкантов", -1, color::cyan);

            break;
        case 5:
            if (diceGame()) {
                print("Вы весело провели время и выиграли немного денег!", -1, color::green);
            }
            else {
                print("Вы проиграли, но хорошо провели время!", -1, color::yellow);
            }

            break;
        case 0:
            print("Вы вышли из таверны", -1, color::blue);
            city();
            break;
        default:
            print("Нет такого варианта ответа", -1, color::bright_red);
            break;;
        }
    } while (choice != 0);

    wait(0.5);
    system("cls");
}

void menuLocation(); // Forward-декларация

int city() {
    system("cls");
    int choice;


    print("В городе есть такие места как:");
    print("Библиотека (1) \nВаш дом (2) \nТаверна (3) \nУйти из города (0) ", -1, color::yellow);
    print("Введите цифру места что бы туда пойти ", -1, color::blue);
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
            print("Вы ушли из города", -1, color::blue);
            menuLocation();
            break;
        case 666:
            hrprint("тебе пока что нельзя сюда ", 200, color::bright_red);
            break;
        default:
            print("Нет такого варианта ответа", -1, color::bright_red);
            break;
        }
    } while (choice != 0);

    return 0;
}

void menuLocation() {
    system("cls");
    int choice;
    print("Куда вы хотите пойти");
    print("Город (1)\nПещера (2)\nГлавное меню (0)", -1, color::yellow);
    do {
        choice = rightValue();
        switch (choice) {
        case(1):
            city();
            break;
        case(2):
            break;
        case(0):
            startMenu();
            break;
        default:
            print("Нет такого варианта ответа", -1, color::bright_red);
            break;
        }
    } while (choice != 0);
    wait(0.5);
    system("cls");
}
void achievements() {
    int choice;

    do {
        system("cls");
        print("=== ДОСТИЖЕНИЯ ===", 1, color::cyan);

        // Проверяем достижения
        if (Taverncheck && homecheck && Librarycheck) {
            print("✓ Посетить все локации - ВЫПОЛНЕНО", textSpeed, color::green);
        }
        else {
            print("✗ Посетить все локации - НЕ ВЫПОЛНЕНО", textSpeed, color::bright_red);
        }

        print("\n0 - Вернуться в меню", 1, color::red);
        print("Выберите вариант: ", 1, color::blue);

        choice = rightValue();

        switch (choice) {
        case 0:
            print("Возврат в меню...", textSpeed, color::blue);
            startMenu();
            break;
        default:
            print("Нет такого варианта ответа", textSpeed, color::bright_red);
            wait(1);
            break;
        }
    } while (choice != 0);
}
int startMenu() {
    int choice;
    system("cls");
    print("Добро пожаловать в игру NNNNNN", textSpeed, color:: none);
    print("Начать игру (1)", -1, color::green);
    print("Настройки (2)", -1, color::none);
    print("Достижения (3)", -1, color::none);
    print("Выйти из игры (0)", -1, color::red);
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
        case 0:
            print("Спасибо за игру! До свидания!", 30, color::green);
            wait(1);
            return 0;
        default:
            print("Нет такого варианта ответа", -1, color::bright_red);
            break;
        }

        wait(0.5);
    } while (choice != 0);

    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");

    startMenu();

    

    return 0;
}