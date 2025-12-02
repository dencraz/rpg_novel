#include "City.h"
#include "LocationMenu.h"
#include "Player.h"
#include "Item.h"
#include "MainMenu.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;
using namespace utils;
using namespace utils::color;


bool City::minerTalkedAboutBoss = false;

City::City() : locationMenuPtr(nullptr), playerPtr(nullptr) {}

City::~City() {}

void City::setLocationMenu(LocationMenu* locMenu) {
    locationMenuPtr = locMenu;
}

void City::setPlayer(Player* player) {
    playerPtr = player;
}

string City::getDescription() const {
    return "Вы находитесь в оживленном средневековом городе.";
}

// Реализация шахтера
void City::talkToMiner() {
    if (!playerPtr) return;

    int choice;
    static bool firstMeeting = true;

    do {
        system("cls");

        cout << yellow << "+----------------------------------------------------------+" << none << endl;
        cout << yellow << "|" << gray << "                  *** СТАРЫЙ ШАХТЁР ***                   " << yellow << "|" << none << endl;
        cout << yellow << "+----------------------------------------------------------+" << none << endl;
        cout << endl;

        if (firstMeeting) {
            print("Старый шахтёр: Новое лицо... Присаживайся, если хочешь", textSpeed, gray);
            print("послушать старые истории.", textSpeed, gray);
            firstMeeting = false;
        }
        else {
            print("Старый шахтёр: О, снова ты. Есть что спросить?", textSpeed, gray);
        }

        cout << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << green << "[1]" << cyan << " Расскажите о пещерах" << string(33, ' ') << "|" << none << endl;
        cout << cyan << "| " << green << "[2]" << cyan << " Я не верю в сказки" << string(35, ' ') << "|" << none << endl;
        cout << cyan << "| " << green << "[3]" << cyan << " Может, лучше про город расскажете?" << string(19, ' ') << "|" << none << endl;

        // Показываем опцию про опасность, если еще не разблокирован босс
        if (!minerTalkedAboutBoss) {
            cout << cyan << "| " << red << "[4]" << cyan << " Расскажите о чём-то действительно опасном" << string(12, ' ') << "|" << none << endl;
        }

        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << yellow << "[0]" << cyan << " Закончить разговор" << string(35, ' ') << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        cout << blue << "Ваш выбор: " << none;
        choice = rightValue();

        switch (choice) {
        case 1:
        case 2:
            system("cls");
            print("Старый шахтёр: В Старых рудниках есть залежи синего кристалла.", textSpeed, gray);
            print("Днём они холодные как лёд, а ночью светятся.", textSpeed, cyan);
            print("Мы их 'ночными свечами' звали.", textSpeed, gray);
            cout << endl;
            print("Вы: 'И что в них особенного?'", textSpeed, yellow);
            cout << endl;
            print("Старый шахтёр: А то, что они растут. Медленно...", textSpeed, gray);
            print("Но если отметить место и вернуться через год -", textSpeed, gray);
            print("увидишь, как кристалл продвинулся на ладонь.", textSpeed, cyan);
            wait(5);
            break;

        case 3:
            system("cls");
            print("Старый шахтёр: Помню, когда на месте этой таверны стояла", textSpeed, gray);
            print("кузница старого Генри. Как он бил молотом... весь район слышал.", textSpeed, gray);
            cout << endl;
            print("Вы: 'Что случилось с кузницей?'", textSpeed, yellow);
            cout << endl;
            print("Старый шахтёр: Генри ушёл в пещеры за редкой рудой...", textSpeed, gray);
            print("и не вернулся. Говорят, он нашёл то, что искал,", textSpeed, red);
            print("но цена была слишком высока...", textSpeed, red);
            wait(5);
            break;

        case 4:
            if (!minerTalkedAboutBoss) {
                system("cls");
                cout << red << "+============================================================+" << none << endl;
                cout << red << "|" << yellow << "              *** ИСТОРИЯ О КАМЕННОМ ПОЖИРАТЕЛЕ ***         " << red << "|" << none << endl;
                cout << red << "+============================================================+" << none << endl;
                cout << endl;

                print("Старый шахтёр: Ты... не похож на обычных любопытных.", textSpeed, gray);
                print("В глазах вижу — ты ещё не знаешь, какой ужас", textSpeed, gray);
                print("скрывается в глубине.", textSpeed, red);
                cout << endl;
                wait(2);

                print("Старый шахтёр: В Заброшенной шахте живёт нечто...", textSpeed, gray);
                print("Каменный Пожиратель. Мы даже не пытались сражаться —", textSpeed, red);
                print("один вид отбивал всякое желание приближаться.", textSpeed, red);
                cout << endl;
                wait(2);

                print("Вы: 'Что она собой представляет?'", textSpeed, yellow);
                cout << endl;

                print("Старый шахтёр: Огромное... тело будто из чёрного камня.", textSpeed, gray);
                print("Оно не просто нападает — оно поглощает.", textSpeed, red);
                print("Растворяет всё на своём пути.", textSpeed, red);
                cout << endl;
                wait(2);

                print("Вы: 'Она убивает?'", textSpeed, yellow);
                cout << endl;

                print("Старый шахтёр: Мы не остались проверять.", textSpeed, gray);
                print("Видели, как оно втянуло в каменную стену", textSpeed, gray);
                print("целую телегу с оборудованием... и та просто исчезла.", textSpeed, red);
                print("В шахтах до сих пор видны очертания тех, кто не успел убежать —", textSpeed, red);
                print("словно тени, вмёрзшие в породу.", textSpeed, bright_red);
                cout << endl;
                wait(3);

                print("Вы: 'Как её победить?'", textSpeed, yellow);
                cout << endl;

                print("Старый шахтёр: Мы даже не пытались!", textSpeed, gray);
                print("Какие там мечи или кирки... Когда слышишь этот скрежет", textSpeed, gray);
                print("камня о камень, видишь, как стены начинают шевелиться —", textSpeed, red);
                print("есть только одна мысль: бежать!", textSpeed, bright_red);
                cout << endl;
                wait(3);

                cout << green << "+----------------------------------------------------------+" << none << endl;
                cout << green << "|  Теперь доступна новая локация: ЗАБРОШЕННАЯ ШАХТА        |" << none << endl;
                cout << green << "+----------------------------------------------------------+" << none << endl;

                minerTalkedAboutBoss = true;
                wait(3);
            }
            break;

        case 0:
            print("Вы прощаетесь со старым шахтёром.", textSpeed, gray);
            wait(1);
            return;

        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }
    } while (choice != 0);
}

bool City::diceGame() {
    print("Вы бросаете кости...", textSpeed, yellow);
    wait(1);

    int playerRoll = utils::random(1, 6) + utils::random(1, 6);
    int enemyRoll = utils::random(1, 6) + utils::random(1, 6);

    print("Ваш бросок: " + to_string(playerRoll), textSpeed, cyan);
    print("Бросок противника: " + to_string(enemyRoll), textSpeed, red);

    if (playerRoll > enemyRoll) {
        print("Вы победили!", textSpeed, green);
        return true;
    }
    else if (playerRoll < enemyRoll) {
        print("Вы проиграли!", textSpeed, red);
        return false;
    }
    else {
        print("Ничья! Ставка возвращена.", textSpeed, yellow);
        if (playerPtr) {
            playerPtr->addGold(50);
        }
        return false;
    }
}

void City::visitHome() {
    if (!playerPtr) {
        print("Ошибка: игрок не найден!", textSpeed, red);
        wait(2);
        return;
    }

    int choice;
    bool catFed = false;

    do {
        system("cls");
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "|" << yellow << "                     *** ДОМ ***                          " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "|" << gray << "  Родные стены. Здесь пахнет деревом и сушеными травами.  " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        cout << cyan << "| " << green << "[1]" << cyan << " Поспать (Восстановить HP/Ману)" << string(21, ' ') << "|" << none << endl;
        cout << cyan << "| " << green << "[2]" << cyan << " Посмотреть профиль" << string(33, ' ') << "|" << none << endl;
        cout << cyan << "| " << green << "[3]" << cyan << " Сделать зарядку (-10 маны)" << string(25, ' ') << "|" << none << endl;
        cout << cyan << "| " << green << "[4]" << cyan << " Покормить кота Барсика" << string(29, ' ') << "|" << none << endl;
        cout << cyan << "| " << green << "[5]" << cyan << " Погладить кота" << string(37, ' ') << "|" << none << endl;

        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << red << "[0]" << cyan << " Выйти из дома" << string(38, ' ') << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        cout << blue << "Ваш выбор: " << none;
        choice = rightValue();

        switch (choice) {
        case 1: {
            // Сон
            int hoursSlept = random(4, 12);
            print("Вы ложитесь в мягкую кровать...", textSpeed, green);
            wait(1);
            print("Снятся странные сны о подземельях...", textSpeed, gray);
            wait(1);
            print("Вы проспали " + to_string(hoursSlept) + " часов.", textSpeed, yellow);

            playerPtr->setCurrentHP(playerPtr->getMaxHP());
            playerPtr->setCurrentMana(playerPtr->getMaxMana());

            print("Силы полностью восстановлены!", textSpeed, green);
            wait(2);
            break;
        }
        case 2:
            system("cls");
            if (playerPtr) {
                playerPtr->showProfile(playerPtr);
            }
            cout << endl;
            print("Нажмите Enter, чтобы продолжить...", textSpeed, gray);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        case 3: {
            if (playerPtr->getCurrentMana() >= 10) {
                playerPtr->useMana(10);
                print("Вы делаете серию отжиманий и приседаний...", textSpeed, cyan);
                wait(2);

                int trainChance = random(1, 100);
                if (trainChance <= 15) {
                    playerPtr->setMaxHP(playerPtr->getMaxHP() + 1);
                    playerPtr->setCurrentHP(playerPtr->getCurrentHP() + 1);
                    print("Вы чувствуете прилив сил! Макс. HP увеличено на 1!", textSpeed, green);
                }
                else {
                    print("Вы немного устали, но чувствуете себя бодрее.", textSpeed, yellow);
                }
            }
            else {
                print("Вы слишком устали для тренировки (нужно 10 маны).", textSpeed, red);
            }
            wait(2);
            break;
        }
        case 4: {
            if (!catFed) {
                print("Вы даете коту кусочек рыбы.", textSpeed, green);
                print("Барсик довольно чавкает.", textSpeed, cyan);
                catFed = true;
            }
            else {
                print("Барсик уже сыт и лениво смотрит на еду.", textSpeed, gray);
            }
            wait(2);
            break;
        }
        case 5: {
            // Гладим кота
            print("Вы гладите Барсика...", textSpeed, yellow);
            wait(1);
            print("Муррр...", textSpeed, cyan);

            // Шанс 25% на появление странной картинки
            if (random(1, 100) <= 50) {
                wait(1);
                cout << yellow << R"(
                         _                     
                      ______                  
                     ||   ___                 
                     ||     _/_               
                     _|       _/__________    
                      |_       __|_      ._   
            ___        /_                 /_  
           || ___      _/         ____    _/  
          _.    ._      _.      ___        _| 
         _./_.._...     _\_     .           . 
    __________..|_   _..   _\_      || ___      |_
    .__....___||       .|___         .\__      _\ 
    _...........       |._           _/_____ ___  
     |.|..*......_____.._             _._ ____    
      /_.........|__.._            ________       
       _........*____       ________              
         __...__.|     _______                    
           |_   _._     _/                        
          _|   _.._      _/_                      
          ||  ||||   .__   /_                     
          ||___  |   | _.   |__                   
           __    .  ||  _|   _._                  
                 .| |    ______                   
                _|  ||                            
                ______
                    )" << none << endl;
                print("Что-то странное померещилось...", textSpeed, magenta);
            }
            wait(4);
            break;
        }
        case 0:
            print("Вы берете снаряжение и выходите на улицу...", textSpeed, none);
            wait(1);
            return;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }
    } while (choice != 0);
}


void City::visitLibrary() {
    if (!playerPtr) {
        print("Ошибка: игрок не найден!", textSpeed, red);
        wait(2);
        return;
    }

    int choice;

    do {
        system("cls");
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "|" << yellow << "                  *** БИБЛИОТЕКА ***                      " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "|" << gray << "  Древние книги хранят знания прошлого...                 " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << green << "[1]" << cyan << " Изучить книгу о боевых искусствах - " << yellow << "100 золота" << string(9, ' ') << cyan << "|" << none << endl;
        cout << cyan << "|" << gray << "     Увеличить максимальное HP на 10                      " << cyan << "|" << none << endl;
        cout << cyan << "| " << green << "[2]" << cyan << " Изучить книгу о магии - " << yellow << "100 золота" << string(21, ' ') << cyan << "|" << none << endl;
        cout << cyan << "|" << gray << "     Увеличить максимальную ману на 10                    " << cyan << "|" << none << endl;
        cout << cyan << "| " << green << "[3]" << cyan << " Почитать для удовольствия (бесплатно)" << string(18, ' ') << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << red << "[0]" << cyan << " Выйти из библиотеки" << string(35, ' ') << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        cout << blue << "Ваш выбор: " << none;
        choice = rightValue();

        switch (choice) {
        case 1:
            if (playerPtr->getGold() >= 100) {
                playerPtr->spendGold(100);
                playerPtr->setMaxHP(playerPtr->getMaxHP() + 10);
                playerPtr->setCurrentHP(playerPtr->getCurrentHP() + 10);
                print("Вы изучили боевые техники!", textSpeed, green);
                print("Максимальное HP увеличено на 10!", textSpeed, yellow);
                print("Новое HP: " + to_string(playerPtr->getCurrentHP()) + "/" + to_string(playerPtr->getMaxHP()), textSpeed, cyan);
            }
            else {
                print("Недостаточно золота!", textSpeed, red);
            }
            wait(3);
            break;

        case 2:
            if (playerPtr->getGold() >= 100) {
                playerPtr->spendGold(100);
                playerPtr->setMaxMana(playerPtr->getMaxMana() + 10);
                playerPtr->setCurrentMana(playerPtr->getCurrentMana() + 10);
                print("Вы изучили магические знания!", textSpeed, green);
                print("Максимальная мана увеличена на 10!", textSpeed, yellow);
                print("Новая мана: " + to_string(playerPtr->getCurrentMana()) + "/" + to_string(playerPtr->getMaxMana()), textSpeed, cyan);
            }
            else {
                print("Недостаточно золота!", textSpeed, red);
            }
            wait(3);
            break;

        case 3:
            print("Вы читаете увлекательную книгу...", textSpeed, cyan);
            print("Это было интересно!", textSpeed, green);
            wait(2);
            break;

        case 0:
            print("Вы вышли из библиотеки", textSpeed, none);
            wait(1);
            return;

        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }
    } while (choice != 0);
}

void City::visitTavern() {
    if (!playerPtr) {
        print("Ошибка: игрок не найден!", textSpeed, red);
        wait(2);
        return;
    }

    // Начальное предупреждение
    if (playerPtr->getAge() < 18) {
        system("cls");
        cout << red << "+----------------------------------------------------------+" << none << endl;
        cout << red << "|" << yellow << "                   *** ТАВЕРНА ***                       " << red << "|" << none << endl;
        cout << red << "+----------------------------------------------------------+" << none << endl;
        print("Бармен смотрит на вас с недовольством:", textSpeed, red);
        print("'Эй, малыш! Тебе сюда ещё рано!'", textSpeed, bright_red);
        print("'Ладно уж, заходи, но без алкоголя!'", textSpeed, yellow);
        print("'И не вздумай играть в азартные игры!'", textSpeed, red);
        wait(4);
    }

    int choice;
    int underageGamblingAttempts = 0; // Счетчик попыток сыграть для несовершеннолетних

    do {
        system("cls");
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "|" << yellow << "                   *** ТАВЕРНА ***                       " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "|" << gray << "  Шумное место, полное веселья и азартных игр...          " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << green << "[1]" << cyan << " Купить эль (восстановить 20 HP) - " << yellow << "30 золота" << string(9, ' ') << cyan << "|" << none << endl;
        cout << cyan << "| " << green << "[2]" << cyan << " Поговорить с барменом (слухи и сплетни)" << string(15, ' ') << "|" << none << endl;
        cout << cyan << "| " << green << "[3]" << cyan << " Послушать музыкантов (восстановить ману)" << string(13, ' ') << "|" << none << endl;
        cout << cyan << "| " << yellow << "[4]" << cyan << " Игра в кости - Испытать удачу! - " << yellow << "50 золота" << string(9, ' ') << cyan << "|" << none << endl;
        cout << cyan << "| " << gray << "[5]" << cyan << " Поговорить со старым шахтёром" << string(24, ' ') << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << red << "[0]" << cyan << " Выйти из таверны" << string(37, ' ') << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        cout << blue << "Ваш выбор: " << none;
        choice = rightValue();

        switch (choice) {
        case 1:
            if (playerPtr->getAge() < 18) {
                print("Бармен качает головой:", textSpeed, red);
                print("'Нет-нет! Тебе ещё рано пить эль, малыш!'", textSpeed, bright_red);
                print("'Держи лучше яблочный сок... Бесплатно.'", textSpeed, yellow);
                playerPtr->heal(10);
                print("Вы выпили сок и восстановили 10 HP", textSpeed, green);
                print("Текущее HP: " + to_string(playerPtr->getCurrentHP()) + "/" + to_string(playerPtr->getMaxHP()), textSpeed, yellow);
            }
            else {
                if (playerPtr->getGold() >= 30) {
                    playerPtr->spendGold(30);
                    playerPtr->heal(20);
                    print("Вы выпили пенного эля и восстановили 20 HP!", textSpeed, green);
                    print("Текущее HP: " + to_string(playerPtr->getCurrentHP()) + "/" + to_string(playerPtr->getMaxHP()), textSpeed, yellow);
                }
                else {
                    print("Недостаточно золота!", textSpeed, red);
                }
            }
            wait(3);
            break;

        case 2: {
            int chance = random(1, 100);
            if (chance < 30) {
                print("Бармен таинственно шепчет:", textSpeed, magenta);
                print("'Слышал, в пещере появился редкий монстр!'", textSpeed, yellow);
                print("'Говорят, он охраняет несметные сокровища...'", textSpeed, yellow);
            }
            else if (chance < 60) {
                print("Бармен рассказывает:", textSpeed, magenta);
                print("'В библиотеке можно улучшить свои навыки за золото.'", textSpeed, cyan);
            }
            else {
                print("Бармен делится новостями:", textSpeed, magenta);
                print("'Торговец получил новую партию зелий. Цены не низкие!'", textSpeed, gray);
            }
            wait(3);
            break;
        }

        case 3:
            print("Вы слушаете красивую мелодию менестреля...", textSpeed, cyan);
            playerPtr->restoreMana(30);
            print("Восстановлено 30 маны! Текущая мана: " + to_string(playerPtr->getCurrentMana()), textSpeed, green);
            wait(3);
            break;

        case 4:
            if (playerPtr->getAge() < 18) {
                // Увеличиваем счетчик попыток
                underageGamblingAttempts++;

                // Если попыток 5 или больше - выкидываем
                if (underageGamblingAttempts >= 5) {
                    system("cls");
                    print("Бармен бьет кружкой по столу, его лицо краснеет от гнева:", textSpeed, red);
                    print("'ВСЁ! МОЁ ТЕРПЕНИЕ ЛОПНУЛО!'", textSpeed, bright_red);
                    print("'Я же сказал - пошел вон отсюда, щенок!'", textSpeed, bright_red);
                    wait(2);
                    print("Охранник хватает вас за шиворот и вышвыривает на улицу.", textSpeed, gray);
                    print("Вы больно ударились о брусчатку.", textSpeed, yellow);
                    playerPtr->takeDamage(5); // Небольшой урон за вылет
                    print("Получено 5 урона.", textSpeed, red);
                    wait(3);
                    return; // ПРИНУДИТЕЛЬНЫЙ ВЫХОД ИЗ ТАВЕРНЫ
                }

                // Обычное предупреждение (если попыток < 5)
                print("Бармен строго смотрит на вас:", textSpeed, red);

                if (underageGamblingAttempts == 4) {
                    print("'Это последнее предупреждение! Ещё раз спросишь - вылетишь отсюда!'", textSpeed, bright_red);
                }
                else {
                    print("'Я же сказал - никаких азартных игр!'", textSpeed, bright_red);
                    print("'Ты слишком молод для этого!'", textSpeed, yellow);
                }
                wait(3);
            }
            else {
                // Логика для взрослых (18+)
                if (playerPtr->getGold() >= 50) {
                    playerPtr->spendGold(50);
                    if (diceGame()) {
                        int winAmount = random(75, 150);
                        playerPtr->addGold(winAmount);
                        print("Вы выиграли " + to_string(winAmount) + " золота!", textSpeed, green);
                    }
                    else {
                        print("Удача не на вашей стороне...", textSpeed, yellow);
                    }
                }
                else {
                    print("Нужно 50 золота для игры!", textSpeed, red);
                }
                wait(3);
            }
            break;

        case 5:
            talkToMiner();
            break;

        case 0:
            print("Вы вышли из таверны", textSpeed, none);
            wait(1);
            return;

        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }
    } while (choice != 0);
}


void City::visitShop() {
    // (твой код магазина без изменений)
    if (!playerPtr) {
        print("Ошибка: игрок не найден!", textSpeed, red);
        wait(2);
        return;
    }

    int choice;

    do {
        system("cls");
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "|" << yellow << "                   *** ЛАВКА ТОРГОВЦА ***                 " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << green << "Ваше золото: " << yellow << playerPtr->getGold() << string(38 - to_string(playerPtr->getGold()).length(), ' ') << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << green << "[1]" << cyan << " Малое зелье лечения (30 HP) - " << yellow << "50 золота" << string(11, ' ') << cyan << "|" << none << endl;
        cout << cyan << "| " << green << "[2]" << cyan << " Среднее зелье лечения (60 HP) - " << yellow << "100 золота" << string(9, ' ') << cyan << "|" << none << endl;
        cout << cyan << "| " << green << "[3]" << cyan << " Большое зелье лечения (100 HP) - " << yellow << "150 золота" << string(8, ' ') << cyan << "|" << none << endl;
        cout << cyan << "| " << green << "[4]" << cyan << " Малое зелье маны (25 маны) - " << yellow << "40 золота" << string(12, ' ') << cyan << "|" << none << endl;
        cout << cyan << "| " << green << "[5]" << cyan << " Среднее зелье маны (50 маны) - " << yellow << "80 золота" << string(10, ' ') << cyan << "|" << none << endl;
        cout << cyan << "| " << green << "[6]" << cyan << " Большое зелье маны (75 маны) - " << yellow << "120 золота" << string(9, ' ') << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << red << "[0]" << cyan << " Выйти из лавки" << string(38, ' ') << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        cout << blue << "Ваш выбор: " << none;
        choice = rightValue();

        switch (choice) {
        case 1:
            if (playerPtr->getGold() >= 50) {
                playerPtr->spendGold(50);
                playerPtr->addItem(Item("Малое зелье лечения", ItemType::POTION, 50, "Восстанавливает 30 HP", 1, 30, 0));
                print("Вы купили Малое зелье лечения!", textSpeed, green);
            }
            else {
                print("Недостаточно золота!", textSpeed, red);
            }
            wait(2);
            break;
        case 2:
            if (playerPtr->getGold() >= 100) {
                playerPtr->spendGold(100);
                playerPtr->addItem(Item("Среднее зелье лечения", ItemType::POTION, 100, "Восстанавливает 60 HP", 1, 60, 0));
                print("Вы купили Среднее зелье лечения!", textSpeed, green);
            }
            else {
                print("Недостаточно золота!", textSpeed, red);
            }
            wait(2);
            break;
        case 3:
            if (playerPtr->getGold() >= 150) {
                playerPtr->spendGold(150);
                playerPtr->addItem(Item("Большое зелье лечения", ItemType::POTION, 150, "Восстанавливает 100 HP", 1, 100, 0));
                print("Вы купили Большое зелье лечения!", textSpeed, green);
            }
            else {
                print("Недостаточно золота!", textSpeed, red);
            }
            wait(2);
            break;
        case 4:
            if (playerPtr->getGold() >= 40) {
                playerPtr->spendGold(40);
                playerPtr->addItem(Item("Малое зелье маны", ItemType::POTION, 40, "Восстанавливает 25 маны", 1, 0, 25));
                print("Вы купили Малое зелье маны!", textSpeed, green);
            }
            else {
                print("Недостаточно золота!", textSpeed, red);
            }
            wait(2);
            break;
        case 5:
            if (playerPtr->getGold() >= 80) {
                playerPtr->spendGold(80);
                playerPtr->addItem(Item("Среднее зелье маны", ItemType::POTION, 80, "Восстанавливает 50 маны", 1, 0, 50));
                print("Вы купили Среднее зелье маны!", textSpeed, green);
            }
            else {
                print("Недостаточно золота!", textSpeed, red);
            }
            wait(2);
            break;
        case 6:
            if (playerPtr->getGold() >= 120) {
                playerPtr->spendGold(120);
                playerPtr->addItem(Item("Большое зелье маны", ItemType::POTION, 120, "Восстанавливает 75 маны", 1, 0, 75));
                print("Вы купили Большое зелье маны!", textSpeed, green);
            }
            else {
                print("Недостаточно золота!", textSpeed, red);
            }
            wait(2);
            break;
        case 0:
            print("Вы вышли из лавки", textSpeed, none);
            wait(1);
            return;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }
    } while (choice != 0);
}

void City::enter() {
    if (!playerPtr) {
        cout << red << "Ошибка: игрок не найден!" << none << endl;
        return;
    }

    int choice;

    do {
        system("cls");

        cout << green << "+----------------------------------------------------------+" << none << endl;
        cout << green << "|" << yellow << "                    *** ГОРОД ***                         " << green << "|" << none << endl;
        cout << green << "+----------------------------------------------------------+" << none << endl;
        cout << green << "| Игрок: " << yellow << playerPtr->getName() << green;
        cout << string(44 - playerPtr->getName().length(), ' ') << "|" << none << endl;
        cout << green << "| HP: " << yellow << playerPtr->getCurrentHP() << "/" << playerPtr->getMaxHP()
            << green << " | Мана: " << cyan << playerPtr->getCurrentMana() << "/" << playerPtr->getMaxMana()
            << green << " | Золото: " << yellow << playerPtr->getGold() << green << "           |" << none << endl;
        cout << green << "+----------------------------------------------------------+" << none << endl;
        cout << endl;

        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "|" << yellow << "              Куда вы хотите пойти?                       " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << green << "[1]" << cyan << " Дом" << string(50, ' ') << "|" << none << endl;
        cout << cyan << "|" << gray << "     Отдохнуть и восстановить HP/ману                     " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << green << "[2]" << cyan << " Библиотека" << string(44, ' ') << "|" << none << endl;
        cout << cyan << "|" << gray << "     Изучить книги и улучшить характеристики              " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << green << "[3]" << cyan << " Таверна" << string(47, ' ') << "|" << none << endl;
        cout << cyan << "|" << gray << "     Выпить, послушать музыку, сыграть в кости            " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << green << "[4]" << cyan << " Лавка торговца" << string(40, ' ') << "|" << none << endl;
        cout << cyan << "|" << gray << "     Купить зелья лечения и маны                          " << cyan << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;
        cout << cyan << "| " << red << "[0]" << cyan << " Вернуться в меню локаций" << string(30, ' ') << "|" << none << endl;
        cout << cyan << "+----------------------------------------------------------+" << none << endl;

        cout << blue << "Ваш выбор: " << none;
        choice = rightValue();

        switch (choice) {
        case 1:
            visitHome();
            break;
        case 2:
            visitLibrary();
            break;
        case 3:
            visitTavern();
            break;
        case 4:
            visitShop();
            break;
        case 0:
            print("Вы покидаете город...", textSpeed, cyan);
            wait(1);
            if (locationMenuPtr) {
                locationMenuPtr->show();
            }
            return;
        default:
            print("Нет такого варианта ответа", textSpeed, red);
            wait(1);
            break;
        }
    } while (choice != 0);
}
