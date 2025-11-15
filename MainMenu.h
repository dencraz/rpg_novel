#pragma once


class LocationMenu;

class MainMenu {
private:
    LocationMenu* locationMenuPtr;

    void showSettings();
    void showAchievements();

public:
    MainMenu(LocationMenu* locMenu);
    void show();
};



