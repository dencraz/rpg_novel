#pragma once
#include "Player.h"

class LocationMenu;

class MainMenu : protected Player {
private:
    LocationMenu* locationMenuPtr;

    void showSettings();
    void showAchievements();

public:
    MainMenu(LocationMenu* locMenu);
    void show();
};
