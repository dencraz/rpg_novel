


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "City.h"
#include "Dungeon.h"  
#include "LocationMenu.h"
#include "MainMenu.h"
#include "Player.h"

int main() {
    setlocale(LC_ALL, "Russian");
    

    // Создаём игрока
    Player player;

    // Создаём город
    City city;

    // Создаём подземелье
    Dungeon dungeon;

    // Создаём меню выбора локаций
    LocationMenu locationMenu(&city);

    // Устанавливаем подземелье в меню локаций
    locationMenu.setDungeon(&dungeon);

    // Устанавливаем обратные связи
    city.setLocationMenu(&locationMenu);
    dungeon.setLocationMenu(&locationMenu);

    // ВАЖНО: Передаем игрока в подземелье
    dungeon.setPlayer(&player);

    // Создаём главное меню
    MainMenu mainMenu(&locationMenu);
    locationMenu.setMainMenu(&mainMenu);

    // Запускаем игру
    mainMenu.show();

    return 0;
}