#pragma once
#include <string>

// Предварительное объявление классов (Forward declarations)
// Это позволяет избежать ошибок циклической зависимости
class LocationMenu;
class Player;

class Dungeon {
private:
    LocationMenu* locationMenuPtr; // Указатель на меню локаций (для возврата)
    Player* playerPtr;             // Указатель на игрока

public:
    Dungeon();
    ~Dungeon();

    // Методы настройки связей
    void setLocationMenu(LocationMenu* locMenu);
    void setPlayer(Player* player);

    // Основные методы входа
    void enter();           // Обычный вход в подземелье (случайные монстры)
    void enterBossBattle(); // Вход в логово БОССА (Каменный Пожиратель)

    std::string getDescription() const;
};
