#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const char* none = "\033[0m";
const char* red = "\033[31m";
const char* green = "\033[32m";
const char* yellow = "\033[33m";
const char* blue = "\033[34m";
const char* magenta = "\033[35m";
const char* cyan = "\033[36m";
const char* white = "\033[37m";
const char* bright_red = "\033[91m";

void wait(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

void print(const string& text, int time, const char* text_color = none) {
    for (char c : text) {
        cout << text_color << c << none << flush;
        this_thread::sleep_for(chrono::milliseconds(time));
    }
    cout << '\n';
}

void hrprint(const string& text, int time, const char* text_color = red) {
    for (char c : text) {
        cout << text_color << (char)std::toupper(c) << none << flush;
        this_thread::sleep_for(chrono::milliseconds(time));
    }
    cout << '\n';
}



int rightValue() {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            print("Некорректный ввод. Пожалуйста, введите число.", 10, bright_red);

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.clear(); //Сбрасывает флаги состояния ошибок потока
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//Удаляет символы из буфера ввода.
            return choice;
        }
    }
}

void acthome() {
    system("cls"); 
    int choice;
    bool shouldContinue = true;

    print("Вы зашли к себе домой", 20, cyan);
    print("Вы видите там", 20, none);
    print("Кровать (1) \nОкно (2) \nКнигу (3) \nВыйти из дома (0) ", 20, yellow);

    do {
        print("Что вы хотите сделать ", 50, blue);
        choice = rightValue();

        switch (choice) {
        case 1:
            print("Вы легли на кровать и уснули", 20, magenta);
            shouldContinue = true;
            break;
        case 2:
            print("Вы посмотрели в окно и увидели оживленный город", 20, cyan);
            shouldContinue = true;
            break;
        case 3:
            print("Вы взяли книгу в руки открыли и немного почитали её", 20, green);
            shouldContinue = true;
            break;
        case 0:
            print("Вы вышли из дома", 20, blue);
            shouldContinue = false;
            break;
        default:
            print("Вы ничего не сделали", 20, bright_red);
            shouldContinue = true;
            break;
        }
    } while (shouldContinue);
    wait(1);
    system("cls");
}

void actLibrary() {
    system("cls");
    int choice;
    bool shouldContinue = true;

    print("Вы зашли в тихую библиотеку", 20, cyan);
    print("Вы видите там", 20, none);
    print("Стеллажи с книгами (1) \nЧитальный зал (2) \nБиблиотекаря (3) \nВыйти из библиотеки (0) ", 20, yellow);

    do {
        print("Что вы хотите сделать ", 50, blue);
        choice = rightValue();

        switch (choice) {
        case 1:
            print("Вы просмотрели старинные книги на полках", 20, green);
            shouldContinue = true;
            break;
        case 2:
            print("Вы устроились в читальном зале и углубились в изучение фолиантов", 20, magenta);
            shouldContinue = true;
            break;
        case 3:
            print("Вы спросили у библиотекаря о редких изданиях", 20, cyan);
            shouldContinue = true;
            break;
        case 0:
            print("Вы вышли из библиотеки", 20, blue);
            shouldContinue = false;
            break;
        default:
            print("Вы ничего не сделали", 20, bright_red);
            shouldContinue = true;
            break;
        }
    } while (shouldContinue);
    wait(1);
    system("cls");
}

bool diceGame() {
    print("Игра в кости! Бросок...", 20, yellow);
    wait(1);

    int playerRoll = rand() % 6 + 1 + rand() % 6 + 1;
    int opponentRoll = rand() % 6 + 1 + rand() % 6 + 1;

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

void actTavern() {
    system("cls");
    int choice;
    bool shouldContinue = true;
    int chance;

    print("Вы зашли в шумную таверну", 20, cyan);
    print("Вы видите там", 20, none);

    print("Барную стойку (1)\nПоговорить с барменом (2) \nИгровой стол (3) \nМузыкантов (4)\nИгра в кости (5) \nВыйти из таверны (0) ", 20, yellow);

    do {
        print("Что вы хотите сделать ", 20, blue);
        choice = rightValue();

        switch (choice) {
        case 1:
            print("Вы подошли к барной стойке и заказали эль", 20, green);
            shouldContinue = true;
            break;
        case 2:
        {
            chance = rand() % 100;

            if (chance < 15) {
                print("У меня для тебя кое что есть ", 20, none);
            }
            else {
                print("Вы хорошо поговорили с барменом на разные темы ", 20, none);
            }
            shouldContinue = true;
            break;
        }
        case 3:
            print("Вы сидели и поиграли с местными жителями", 20, cyan);
            shouldContinue = true;
            break;
        case 4:
            print("Вы послушали веселую музыку местных музыкантов", 20, cyan);
            shouldContinue = true;
            break;
        case 5:
            if (diceGame()) {
                print("Вы весело провели время и выиграли немного денег!", 20, green);
            }
            else {
                print("Вы проиграли, но хорошо провели время!", 20, yellow);
            }
            shouldContinue = true;
            break;
        case 0:
            print("Вы вышли из таверны", 20, blue);
            shouldContinue = false;
            break;
        default:
            print("Вы ничего не сделали", 20, bright_red);
            shouldContinue = true;
            break;
        }
    } while (shouldContinue);

    wait(1);
    system("cls");
}

int city() {
    int choice;

    do {
        print("В городе есть такие места как:", 20, none);
        print("Библиотека (1) \nВаш дом (2) \nТаверна (3) \nВыйти из игры(0) ", 20, yellow);
        print("Введите цифру места что бы туда пойти ", 20, blue);
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
            print("Спасибо за игру! До свидания!", 30, green);
            return 0;
        case 666:
            hrprint("тебе пока что нельзя сюда ", 200, bright_red);
            break;
        default:
            print("Нет такого варианта ответа", 20, bright_red);
            break;
        }
    } while (choice != 0);

    return 0;
}
void startMenu() {
    int choice;
    print("Добро пожаловать в игру NNNNNN", 20, none);
    wait(1);
    print("Начать игру (1)", 20, none);
    print("Настройки (2)", 20, none);
    choice = rightValue();

    switch (choice) {
    case(1):
        city();
    case(2):
        break;

    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    startMenu();

    
    city();

    return 0;
}












