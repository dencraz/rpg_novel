#pragma once

#include <string>

class LocationMenu; // Forward declaration

class City {
private:
    LocationMenu* locationMenuPtr;

    // Приватные методы локаций
    void visitHome();
    void visitLibrary();
    void visitTavern();
    bool diceGame();

public:
    City();

    void setLocationMenu(LocationMenu* locMenu);
    void enter();
    std::string getDescription() const;
};



