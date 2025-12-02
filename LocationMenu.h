#pragma once

class City;
class Dungeon;
class MainMenu;
class Player;

class LocationMenu {
private:
    City* cityPtr;
    Dungeon* dungeonPtr;
    MainMenu* mainMenuPtr;

public:
    LocationMenu(City* city);

    void setDungeon(Dungeon* dungeon);
    void setMainMenu(MainMenu* menu);
    void setPlayerForDungeon(Player* player);  // Передает игрока в город И подземелье
    void show();
};
