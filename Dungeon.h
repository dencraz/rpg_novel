#pragma once
#include <string>

class LocationMenu;
class Player;

class Dungeon {
private:
    LocationMenu* locationMenuPtr;
    Player* playerPtr;

public:
    Dungeon();
    ~Dungeon();

    void setLocationMenu(LocationMenu* locMenu);
    void setPlayer(Player* player);
    void enter();
    std::string getDescription() const;
};
