#pragma once
#include <string>

class LocationMenu;
class Player;

class MainMenu {
private:
    LocationMenu* locationMenuPtr;
    Player* currentPlayer;
    Player* playerPtr;

    void showSettings();
    
   
    void showStoryIntro(const std::string& playerName);

public:
    MainMenu(LocationMenu* locMenu);
    int show();
    Player* getCurrentPlayer() { return currentPlayer; }
    
};
