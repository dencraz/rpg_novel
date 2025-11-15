#pragma once

class City;
class MainMenu; // Forward declaration

class LocationMenu {
private:
    City* cityPtr;
    MainMenu* mainMenuPtr;

public:
    LocationMenu(City* city);
    void setMainMenu(MainMenu* menu);
    void show();
};