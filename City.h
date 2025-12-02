#pragma once
#include <string>

class LocationMenu;
class Player;
class MainMenu;

class City{
private:
    LocationMenu* locationMenuPtr;
    Player* playerPtr;
    MainMenu* mainMenuPtr;
    static bool minerTalkedAboutBoss; 

    void visitHome();
    void visitLibrary();
    void visitTavern();
    void visitShop();
    void talkToMiner(); // Новый метод  
    bool diceGame();

public:
    City();
    ~City();

    void setLocationMenu(LocationMenu* locMenu);
    void setPlayer(Player* player);
    void enter();
    std::string getDescription() const;
    static bool hasMinerUnlockedBoss() { return minerTalkedAboutBoss; }
};
