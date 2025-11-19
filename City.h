#pragma once

#include <string>

class LocationMenu; 

class City {
private:
    LocationMenu* locationMenuPtr;

   
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



