#include <iostream>
#include <cstdlib>
#include <ctime>
#include "City.h"
#include "LocationMenu.h"
#include "MainMenu.h"

int main() {
    setlocale(LC_ALL, "Russian");


    // Создаём город
    City city;

    // Создаём меню выбора локаций
    LocationMenu locationMenu(&city);

    // Устанавливаем обратную связь между City и LocationMenu
    city.setLocationMenu(&locationMenu);

    // Создаём главное меню
    MainMenu mainMenu(&locationMenu);

    // Запуск игры
    mainMenu.show();

    return 0;
}
